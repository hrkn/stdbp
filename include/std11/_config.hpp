/*
 * _config.hpp
 *
 *  Created on: 2013/02/07
 *      Author: hrkn
 */

#ifndef STDBP_STD11_CONFIG_HPP_
#define STDBP_STD11_CONFIG_HPP_

// TODO Refine condition for compiler defines "__cplusplus" as "1"
//      though it suppports C++11.
//      refer: http://gcc.gnu.org/bugzilla/show_bug.cgi?id=1773
#define STDBP_CPP11_ENABLED (__cplusplus >= 201103L)

#if STDBP_CPP11_ENABLED
#warning C++11 has been enabled on this compiler. It is better to use std instead of std11...
#endif

#if STDBP_CPP11_ENABLED
# define STDBP_NOEXCEPT noexcept
#else
# define STDBP_NOEXCEPT throw()
#endif

#endif /* STDBP_STD11_CONFIG_HPP_ */
