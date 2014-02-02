/*
 * string.hpp
 *
 *  Created on: 2013/07/15
 *      Author: Haruki Nakayama
 */

#ifndef STRING_HPP_
#define STRING_HPP_

#include <string>
#include <sstream>

namespace std11
{

template <typename Number>
inline std::string to_string(Number val)
{
	std::stringstream ss;
	ss << val;
	return ss.str();
}

template <typename Number>
inline std::wstring to_wstring(Number val)
{
	std::wstringstream ss;
	ss << val;
	return ss.str();
}

}  // namespace std11

#endif /* STRING_HPP_ */
