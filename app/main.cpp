/**
 * See COPYING file for licensing details.
 */
#include "sk/connectivity_test.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    try {
        sk::HttpHeader::Collection headers;
        headers.push_back(sk::HttpHeader("Test: dfdg"));
        auto test = sk::HttpConnectivityTest::Create("www.google.com");
        auto result(test->Run());

        std::cout<<"SKTEST;"<<result.ip_address<<";"<<std::endl;
    } catch (const std::exception& ex) {
        std::cerr<<"Failed: "<<ex.what()<<std::endl;
    }
	return 0;
}
