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

namespace std
{
// partially specialized pair to avoid "reference of reference" problem
template<class T1, class T2>
struct pair<T1&, T2&>
{
	typedef T1& first_type;
	typedef T2& second_type;
	first_type first;
	second_type second;
	pair(T1& t1, T2& t2) :
			first(t1), second(t2)
	{
	}
	template<class U1, class U2>
	pair(pair<U1, U2> const& p) :
			first(p.first), second(p.second)
	{
	}
	template<class U1, class U2>
	pair& operator=(const pair<U1, U2>& p)
	{
		first = p.first;
		second = p.second;
		return *this;
	}
};
}

namespace std11
{

#if STDBP_CPP11_ENABLED
#define STD11_RV_REF(t)  t&&
using std::move;
#else
#define STD11_RV_REF(t)  std11::RV<t> const

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

using std::pair;

// TODO redefine as which meet C++11 standard
using std::make_pair;

}  // namespace std11

#endif /* STDBP_CPP11_ENABLED */

#endif /* STDBP_STD11_UTILITY_HPP_ */
