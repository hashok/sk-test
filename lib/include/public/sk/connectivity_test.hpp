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

    struct Result {

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
