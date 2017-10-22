/**
 * See COPYING file for licensing details.
 */
#pragma once

#include <string>

namespace sk {

/**
 * User for storing and basic validation of HTTP headers.
 */
class HttpHeader {
public:
	HttpHeader(const std::string& header);

	const std::string& Get() const { return header; }

private:

	const std::string header;

};

} // end of sk namespace
