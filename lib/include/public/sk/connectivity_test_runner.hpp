/**
 * See COPYING file for licensing details.
 */
#pragma once

#include "sk/connectivity_test.hpp"
#include <vector>
#include <algorithm>

namespace sk {

class ConnectivitytestRunner {
public:

    void
    AddTest(HttpConnectivityTest::UniquePtr&& test);

    /**
     * Run all tests and return medians for double values.
     *
     * ip_address and resp_code is taken from an arbitrary test.
     */
    HttpConnectivityTest::Result
    RunTests();

private:

    struct Test {
        HttpConnectivityTest::UniquePtr test;
        HttpConnectivityTest::Result result;
    };

    template<typename Meas>
    static bool
    Compare(const Test& t1, const Test& t2)
    {
        return t1.result.GetScalar(Meas()) < t2.result.GetScalar(Meas());
    }

    /**
     * Calculate median for a given measurement type Meas.
     */
    template<typename Meas>
    void
    CalculateMedian()
    {
        std::sort(tests.begin(), tests.end(), Compare<Meas>);

        result.SetScalar(Meas(), GetMedian<Meas>());
    }

    /**
     * Get median value from a sorted vector.
     */
    template<typename Meas>
    double
    GetMedian()
    {
        if (tests.size() % 2) {
            // Odd, just take middle element directly
            return tests[tests.size() / 2].result.GetScalar(Meas());
        }

        // Even, get average from two middle elements
        auto v1 = tests[tests.size() / 2].result.GetScalar(Meas());
        auto v2 = tests[tests.size() / 2 - 1].result.GetScalar(Meas());

        return (v1 + v2) / 2;
    }

    std::vector<Test> tests;

    HttpConnectivityTest::Result result;
};

}
