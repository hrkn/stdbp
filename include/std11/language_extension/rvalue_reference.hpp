/*
 * rvalue_reference.hpp
 *
 *  Created on: 2014/03/09
 *      Author: Haruki Nakayama
 */

#ifndef STDBP_STD11_RVALUE_REFERENCE_HPP_
#define STDBP_STD11_RVALUE_REFERENCE_HPP_


namespace std11
{

#if STDBP_CPP11_ENABLED
#define STD11_RV_REF(t)  t&&
using std::move;
#else
#define STD11_RV_REF(t)  ::std11::RV<t> const

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

#endif /* STDBP_CPP11_ENABLED */

}

#endif /* STDBP_STD11_RVALUE_REFERENCE_HPP_ */
