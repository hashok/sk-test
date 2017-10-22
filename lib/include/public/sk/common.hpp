/**
 * See COPYING file for licensing details.
 */

#pragma once

namespace std {

/**
 * Helper for creation on unique_ptr objects in C++11
 */
template<typename T, typename ... Args>
std::unique_ptr<T>
make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

} // end of std namespace

namespace sk {

} // end of sk namesapce
