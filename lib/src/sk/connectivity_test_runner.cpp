/**
 * See COPYING file for licensing details.
 */

#include "sk/connectivity_test_runner.hpp"

using namespace sk;

void
ConnectivitytestRunner::AddTest(HttpConnectivityTest::UniquePtr&& test)
{
    tests.emplace_back(Test{std::move(test)});
}

HttpConnectivityTest::Result
ConnectivitytestRunner::RunTests()
{
    if (tests.empty()) {
        throw std::runtime_error("No tests to run");
    }

    for (auto& it : tests) {
        it.result = it.test->Run();
    }

    /* It doesn't make sense to mix medians and values from a single test,
     * but keep it here to adhere to requirements. */
    result.ip_address = tests.begin()->result.ip_address;
    result.resp_code = tests.begin()->result.resp_code;

    CalculateMedian<HttpConnectivityTest::Result::NameLookup>();
    CalculateMedian<HttpConnectivityTest::Result::Connect>();
    CalculateMedian<HttpConnectivityTest::Result::StartTransfer>();
    CalculateMedian<HttpConnectivityTest::Result::Total>();

    return result;

}
