/**
 * See COPYING file for licensing details.
 */

#include "sk/http_header.hpp"
#include <algorithm>

using namespace sk;

HttpHeader::HttpHeader(const std::string& header) :
    header(header)
{
    // The very basic tests so far
    if (header.find("\r\n") != header.npos) {
        throw std::runtime_error("Bad header: cr,lf pair found");
    }

    if (header.find(':') == header.npos) {
        throw std::runtime_error("Bad header: no ':' separator found");
    }
}
