/**
 * See COPYING file for licensing details.
 */
#include "sk/connectivity_test_impl.hpp"
#include "sk/common.hpp"
#include <curl/curl.h>

using namespace sk;

HttpConnectivityTest::UniquePtr
HttpConnectivityTest::Create(
    const std::string& address,
    const HttpHeader::Collection& headers,
    bool secure)
{
    return HttpConnectivityTestImpl::Create(headers, address, secure);
}

HttpConnectivityTest::Result
HttpConnectivityTest::Run()
{
    return HttpConnectivityTest::Result();
}
