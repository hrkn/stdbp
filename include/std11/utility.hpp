/*
 * utility.hpp
 *
 *  Created on: 2013/02/20
 *      Author: hrkn
 */

#ifndef STDBP_STD11_UTILITY_HPP_
#define STDBP_STD11_UTILITY_HPP_

#include <utility>
#include "std11/_config.hpp"

namespace std11
{

#if STD11_CPP11_ENABLED
#define STD11_RV_REF(t)  t&&
using std::move;
#else
#define STD11_RV_REF(t)  std11::RV<t> const
#endif

template<typename T>
struct RV
{
	T& instance;
};

// TODO support transferring temporary object
//      like.   some_object obj = std11::move(some_object(foo, bar));
// TODO also care about literal argument ...
//      like.   int i = std11::move(5);
//          -> Is this should be an compilation error??
template<typename T>
STD11_RV_REF(T) move(T const& t)
{
	STD11_RV_REF(T) tobe_moved = { const_cast<T&>(t) };

	return tobe_moved;
}

template<typename T>
STD11_RV_REF(T) move(T& t)
{
	STD11_RV_REF(T) tobe_moved = { t };
	return tobe_moved;
}

}  // namespace std11

#endif /* STDBP_STD11_UTILITY_HPP_ */
