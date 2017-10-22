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

        // SKTEST;<IP address of HTTP server>;<HTTP response code>;<median of CURLINFO_NAMELOOKUP_TIME>;<median of CURLINFO_CONNECT_TIME>;<median of CURLINFO_STARTTRANSFER_TIME>;<median of CURLINFO_TOTAL_TIME>
        std::cout<<"SKTEST;"<<result.ip_address<<";";
        for (const auto& it : {result.name_lookup_time, result.connect_time, result.start_transfer_time, result.total_time}) {
            std::cout<<it<<";";
        }
        std::cout<<std::endl;
    } catch (const std::exception& ex) {
        std::cerr<<"Failed: "<<ex.what()<<std::endl;
    }
	return 0;
}
