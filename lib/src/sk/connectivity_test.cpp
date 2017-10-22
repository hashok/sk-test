/**
 * See COPYING file for licensing details.
 */
#include "sk/connectivity_test_impl.hpp"
#include "sk/common.hpp"
#include <curl/curl.h>

namespace sk {

HttpConnectivityTest::UniquePtr
HttpConnectivityTest::Create(const std::string& address, bool secure)
{
	return HttpConnectivityTestImpl::Create(address, secure);
}


HttpConnectivityTest::Result
HttpConnectivityTest::Run()
{
	return HttpConnectivityTest::Result();
}

} // end of sk namespace
