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
#include "std11/functional.hpp"
#include "std11/language_extension/rvalue_reference.hpp"

namespace std
{
// partially specialized pair to avoid "reference of reference" problem
template<class T1, class T2>
struct pair<T1&, T2>
{
	typedef T1& first_type;
	typedef T2 second_type;
	first_type first;
	second_type second;
	pair(T1& t1, T2 const& t2) :
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

template<class T1, class T2>
struct pair<T1, T2&>
{
	typedef T1 first_type;
	typedef T2& second_type;
	first_type first;
	second_type second;
	pair(T1 const& t1, T2& t2) :
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

using std::pair;

template <typename T1, typename T2>
pair<T1, T2> make_pair(T1 v1, T2 v2)
{
	return pair<T1, T2>(v1, v2);
}

template <typename T1, typename T2>
pair<T1&, T2> make_pair(
		reference_wrapper<T1> const& v1, T2 v2)
{
	return pair<T1&, T2>(v1.get(), v2);
}

template <typename T1, typename T2>
pair<T1, T2&> make_pair(
		T1 v1, reference_wrapper<T2> const& v2)
{
	return pair<T1, T2&>(v1, v2.get());
}

template <typename T1, typename T2>
pair<T1&, T2&> make_pair(
		reference_wrapper<T1> v1, reference_wrapper<T2> const& v2)
{
	return pair<T1&, T2&>(v1.get(), v2.get());
}

}  // namespace std11

#endif /* STDBP_STD11_UTILITY_HPP_ */
