/**
 * See COPYING file for licensing details.
 */
#include "sk/connectivity_test_runner.hpp"
#include <iostream>
#include <unordered_map>
#include <unistd.h>


int main(int argc, char** argv)
{
    int c, n = 0;
    sk::HttpHeader::Collection headers;
    sk::ConnectivitytestRunner runner;
    std::string domain = "www.google.com";

    try {
        while ((c = getopt(argc, argv, "H:n:d:")) != -1) {
            switch (c) {
            case 'H':
                headers.push_back(sk::HttpHeader(optarg));
                break;
            case 'n':
                try {
                    n = std::stoi(optarg);
                } catch(...) {
                    throw std::runtime_error(std::string("Bad value for -n argument: ") + optarg);
                }
                break;
            case 'd':
                domain = optarg;
                break;
            default:
                throw std::runtime_error(std::string("Unknown command line option"));
            }
        }

        if (n <= 0) {
            throw std::runtime_error("Number of tests should be more than 0");
        }

        for (int i = 0; i < n; i++) {
            auto test = sk::HttpConnectivityTest::Create(domain, headers);
            runner.AddTest(std::move(test));
        }
        auto result = runner.RunTests();

        std::cout<<"SKTEST;"<<result.ip_address<<";"<<result.resp_code;
        for (const auto& it : {result.name_lookup_time, result.connect_time, result.start_transfer_time, result.total_time}) {
            std::cout<<";"<<it;
        }
        std::cout<<std::endl;
    } catch (const std::exception& ex) {
        std::cerr<<"Failed: "<<ex.what()<<std::endl;
        return -1;
    }
	return 0;
}
