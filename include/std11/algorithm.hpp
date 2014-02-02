/*
 * algorithm.hpp
 *
 *  Created on: 2013/04/04
 *      Author: hrkn
 */

#ifndef STDBP_STD11_ALGORITHM_HPP_
#define STDBP_STD11_ALGORITHM_HPP_

#include <algorithm>
#include "std11/type_traits.hpp"
#include "std11/random.hpp"
#include "std11/utility.hpp"

namespace std11
{

// 一つでもpredを満たしていなかったらfalse
template<class InputIterator, class Predicate>
bool all_of(InputIterator first, InputIterator last, Predicate pred)
{
	while (first != last)
	{
		if (!static_cast<bool>(pred(*(first++))))
		{
			return false;
		}
	}
	return true;
}

// 一つでもpredを満たしていたらtrue
template<class InputIterator, class Predicate>
bool any_of(InputIterator first, InputIterator last, Predicate pred)
{
	while (first != last)
	{
		if (static_cast<bool>(pred(*(first++))))
		{
			return true;
		}
	}
	return false;
}

// 一つでもpredを満たしていたらfalse
template<class InputIterator, class Predicate>
bool none_of(InputIterator first, InputIterator last, Predicate pred)
{
	while (first != last)
	{
		if (static_cast<bool>(pred(*(first++))))
		{
			return false;
		}
	}
	return true;
}

// predを満たさない最初の要素を返す
template<class InputIterator, class Predicate>
InputIterator find_if_not(InputIterator first, InputIterator last, Predicate pred)
{
	for (; first != last; ++first)
	{
		if (!static_cast<bool>(pred(*first)))
		{
			return first;
		}
	}
	return last;
}

template<class InputIterator, class Size, class OutputIterator>
OutputIterator copy_n(InputIterator first, Size n, OutputIterator result)
{
	for (Size i = 0; i < n ; ++i)
	{
		*(result + i) = *(first + i);
	}
	return result + n;
}

template<class InputIterator, class OutputIterator, class Predicate>
OutputIterator copy_if(InputIterator first, InputIterator last,
		OutputIterator result, Predicate pred)
{
	for (; first != last; ++first)
	{
		if (pred(*first)) { *result++ = *first; }
	}
	return result;
}

template<class InputIterator, class OutputIterator>
OutputIterator move(InputIterator first, InputIterator last,
		OutputIterator result)
{
	while (first != last)
	{
		*result++ = move(*first++);
	}
	return result;
}


template<class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2 move_backward(BidirectionalIterator1 first,
		BidirectionalIterator1 last, BidirectionalIterator2 result)
{
	while (first != last)
	{
		*--result = move(*--last);
	}
	return result;
}

template<class RandomAccessIterator, class RandomNumberGenerator>
void random_shuffle(RandomAccessIterator first, RandomAccessIterator last,
		STD11_RV_REF(RandomNumberGenerator) rand)
{
	if (first == last)
	{
		return;
	}

	RandomNumberGenerator r(rand);
	for (RandomAccessIterator it = first + 1; it != last; ++it)
	{
		std::iter_swap(it, first + r(it - first + 1));
	}
}

template<class RandomAccessIterator, class UniformRandomNumberGenerator>
void shuffle(RandomAccessIterator first, RandomAccessIterator last,
		STD11_RV_REF(UniformRandomNumberGenerator) g)
{
//	if (first == last) { return; }
//
//	typedef typename iterator_traits<RandomAccessIterator>::difference_type distance_type;
//	typedef typename make_unsigned<distance_type>::type unsigned_type;
//	typedef typename uniform_int_distribution<unsigned_type> distribute_type;
//	typedef typename distribute_type::param_type param_type;
//
//	distribute_type d;
//	for (RandomAccessIterator it = first + 1; it != last; ++it)
//	{
//		iter_swap(it, first + d(g, param_type(0, it - first)));
//	}
}

}  // namespace std11

#endif /* STDBP_STD11_ALGORITHM_HPP_ */
