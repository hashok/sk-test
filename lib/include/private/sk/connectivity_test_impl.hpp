/**
 * See COPYING file for licensing details.
 */
#pragma once

#include "sk/connectivity_test.hpp"
#include "sk/common.hpp"
#include <mutex>
#include <curl/curl.h>

namespace sk {

/**
 * Controls CURL global init/cleanup.
 *
 * To save resources, keep CURL initialized only when at least one test is
 * running.
 */
class CurlGlobal {
public:
    using Ptr = std::shared_ptr<CurlGlobal>;
    using WeakPtr = std::weak_ptr<CurlGlobal>;

    CurlGlobal();

    ~CurlGlobal();

    /**
     * Call this before any other CURL operation and keep owning it until
     * all your work with CURL is done.
     */
    static Ptr
    Create();

private:
    /**
     * CURL global init/cleanup are not thread safe, so protect.
     */
    static std::mutex mutex;

    /**
     * Non-owning access to the initialized CURL session.
     */
    static WeakPtr session;
};

/**
 * Class to adapt HttpHeader::Collection to curl_slist.
 */

class CurlHeaders {
public:
    CurlHeaders(const HttpHeader::Collection& headers);

    ~CurlHeaders();

    curl_slist*
    GetList() { return list; };

private:
    void Cleanup();

    curl_slist* list = nullptr;
};

class HttpConnectivityTestImpl: public HttpConnectivityTest {
public:
    using UniquePtr = std::unique_ptr<HttpConnectivityTestImpl>;

    template<typename ... Args>
    HttpConnectivityTestImpl(const HttpHeader::Collection& headers, Args &&... args) :
        HttpConnectivityTest(AllowCtor(), std::forward<Args>(args)...),
        curl_headers(headers)
    {

    }

    ~HttpConnectivityTestImpl();

    template<typename ... Args>
    static UniquePtr
    Create(Args &&... args)
    {
        return std::make_unique<HttpConnectivityTestImpl>(std::forward<Args>(args)...);
    }

    virtual Result
    Run() override;

private:

    /**
     * Does Curl global init and acquires a handle.
     */
    void
    AcquireCurl();

    template<typename ...Args>
    void
    CurlSetOpt(CURLoption opt, Args &&... args)
    {
        auto code = curl_easy_setopt(curl_h, opt, std::forward<Args>(args)...);
        if (code != CURLcode::CURLE_OK) {
            throw std::runtime_error(
                "Failed to set Curl option " + std::to_string(opt) + " :"
                    + curl_easy_strerror(code));
        }
    }

    template<typename ...Args>
    void
    CurlGetInfo(CURLINFO info, Args &&... args)
    {
        auto code = curl_easy_getinfo(curl_h, info, std::forward<Args>(args)...);
        if (code != CURLcode::CURLE_OK) {
            throw std::runtime_error(
                "Failed to get Curl info " + std::to_string(info) + " :"
                + curl_easy_strerror(code));
        }
    }

    CurlGlobal::Ptr curl_global;

    CURL* curl_h = nullptr;

    CurlHeaders curl_headers;

};

} // end of sk namespace
