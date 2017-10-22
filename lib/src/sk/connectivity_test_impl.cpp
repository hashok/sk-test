/**
 * See COPYING file for licensing details.
 */
#include "sk/connectivity_test_impl.hpp"

using namespace sk;

std::mutex CurlGlobal::mutex;

CurlGlobal::WeakPtr CurlGlobal::session;

CurlGlobal::CurlGlobal()
{
    auto code = curl_global_init(CURL_GLOBAL_ALL);
    if (code != CURLcode::CURLE_OK) {
        throw std::runtime_error(
            std::string("CURL global init failed: ")
                + curl_easy_strerror(code));
    }
}

CurlGlobal::~CurlGlobal()
{
    curl_global_cleanup();
}

CurlGlobal::Ptr
CurlGlobal::Create()
{
    std::unique_lock<std::mutex> lock(mutex);

    auto locked = session.lock();

    if (locked) {
        // Init already done, just increase the reference
        return locked;
    }

    locked = std::make_shared<CurlGlobal>();

    session = locked;

    return locked;
}

CurlHeaders::CurlHeaders(const HttpHeader::Collection& headers)
{
    for (const auto& it : headers) {
        auto new_list = curl_slist_append(list, it.Get().c_str());
        if (!new_list) {
            // Cleanup already created list
            Cleanup();
            throw std::runtime_error("Curl slist append failed");
        }
        list = new_list;
    }
}

CurlHeaders::~CurlHeaders()
{
    Cleanup();
}

void
CurlHeaders::Cleanup()
{
    if (list) {
        curl_slist_free_all(list);
    }
}

HttpConnectivityTestImpl::~HttpConnectivityTestImpl()
{
    if (curl_h) {
        curl_easy_cleanup(curl_h);
    }
}

HttpConnectivityTest::Result
HttpConnectivityTestImpl::Run()
{
    AcquireCurl();

    std::string url(secure ? "https://" : "http://");
    url += address;

    CurlSetOpt(CURLoption::CURLOPT_HTTPGET, 1L);
    CurlSetOpt(CURLoption::CURLOPT_URL, url.c_str());
    CurlSetOpt(CURLoption::CURLOPT_HTTPHEADER, curl_headers.GetList());
    /* Avoid ambiguity, use only IPv4 for now.
     * We definitely want to have IPv4/6 statistics separated in future. */
    CurlSetOpt(CURLoption::CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

    auto code = curl_easy_perform(curl_h);

    if (code != CURLcode::CURLE_OK) {
        std::runtime_error(std::string("Curl perform failed: ") + curl_easy_strerror(code));
    }

    Result result;

    {
        char* ip = nullptr;
        CurlGetInfo(CURLINFO::CURLINFO_PRIMARY_IP, &ip);
        // Copy is made implicitly
        result.ip_address = ip;
    }

    return result;
}

void
HttpConnectivityTestImpl::AcquireCurl()
{
    curl_global = CurlGlobal::Create();
    curl_h = curl_easy_init();
    if (!curl_h) {
        throw std::runtime_error("Curl easy init failed");
    }
}
