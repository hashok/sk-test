/**
 * See COPYING file for licensing details.
 */
#pragma once

#include "sk/http_header.hpp"
#include <string>
#include <memory>

namespace sk {

class HttpConnectivityTest {
protected:
    /**
     * Non-public type to protect constructor from using directly.
     *
     * dummy is necessary because of this GCC bug:
     * https://gcc.gnu.org/bugzilla/show_bug.cgi?id=60336
     */
    struct AllowCtor {
        int dummy;
    };

public:
    using UniquePtr = std::unique_ptr<HttpConnectivityTest>;

    /**
     * Fields are as per test requirements.
     */
    struct Result {
        struct NameLookup {};
        struct Connect {};
        struct StartTransfer {};
        struct Total {};

        std::string ip_address;
        long resp_code = 0;

        double name_lookup_time = 0;
        double connect_time = 0;
        double start_transfer_time = 0;
        double total_time = 0;

        double GetScalar(NameLookup) const { return name_lookup_time; }
        double GetScalar(Connect) const { return connect_time; }
        double GetScalar(StartTransfer) const { return start_transfer_time; }
        double GetScalar(Total) const { return total_time; }

        void SetScalar(NameLookup, double value) { name_lookup_time = value; }
        void SetScalar(Connect, double value) { connect_time = value; }
        void SetScalar(StartTransfer, double value) { start_transfer_time = value; }
        void SetScalar(Total, double value) { total_time = value; }
    };

    /**
     * Constructor for internal use only.
     */
    HttpConnectivityTest(
        const AllowCtor&,
        const std::string& address,
        bool secure) :
        address(address), secure(secure) {};

    virtual
    ~HttpConnectivityTest() = default;

    /**
     * Create a new test.
     *
     * address:  Address to connect without protocol part.
     *
     * headers: Additional headers.
     *
     * secure: HTTP or HTTPS.
     */
    static UniquePtr
    Create(
        const std::string& address,
        const HttpHeader::Collection& headers = HttpHeader::Collection(),
        bool secure = false);

    /**
     * Run test synchronously and return the result.
     */
    virtual Result
    Run() = 0;

protected:

    /**
     * URL without a protocol part.
     */
    const std::string address;

    /**
     * HTTP or HTTPS.
     */
    const bool secure;

};

} // end of sk namespace
