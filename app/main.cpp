/**
 * See COPYING file for licensing details.
 */
#include "sk/connectivity_test.hpp"

int main(int argc, char** argv)
{
	auto test = sk::HttpConnectivityTest::Create("www.google.com");
	return 0;
}
