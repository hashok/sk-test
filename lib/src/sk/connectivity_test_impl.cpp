/**
 * See COPYING file for licensing details.
 */
#include "sk/connectivity_test_impl.hpp"

namespace sk {

std::mutex CurlGlobal::mutex;

CurlGlobal::WeakPtr CurlGlobal::session;

CurlGlobal::CurlGlobal()
{
	auto code = curl_global_init(CURL_GLOBAL_ALL);
	if (code != CURLcode::CURLE_OK) {
		throw std::runtime_error(std::string("CURL global init failed: ") +
				curl_easy_strerror(code));
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

	std::string url = secure ? "https://" : "http://";
	url += address;

	CurlSetOpt(CURLoption::CURLOPT_URL, url.c_str());

	return Result();
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


} // end of sk namespace
