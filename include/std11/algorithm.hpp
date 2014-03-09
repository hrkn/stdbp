/*
 * algorithm.hpp
 *
 *  Created on: 2013/04/04
 *      Author: hrkn
 */

#ifndef STDBP_STD11_ALGORITHM_HPP_
#define STDBP_STD11_ALGORITHM_HPP_

#include <algorithm>
#include "std11/functional.hpp"
#include "std11/iterator.hpp"
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

using std::for_each;
using std::find;
using std::find_if;

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

using std::find_end;
using std::find_first_of;
using std::adjacent_find;
using std::count;
using std::count_if;
using std::mismatch;
using std::equal;
using std::search;
using std::search_n;
using std::copy;

template<class InputIterator, class Size, class OutputIterator>
OutputIterator copy_n(InputIterator first, Size n, OutputIterator result)
{
	for (Size i = 0; i < n ; ++i)
	{
		*(result++) = *(first++);
	}
	return result;
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

using std::copy_backward;

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

using std::swap_ranges;
using std::iter_swap;
using std::transform;
using std::replace;
using std::replace_if;
using std::replace_copy;
using std::replace_copy_if;
using std::fill;
using std::fill_n;
using std::generate;
using std::generate_n;
using std::remove;
using std::remove_if;
using std::remove_copy;
using std::remove_copy_if;
using std::unique;
using std::unique_copy;
using std::reverse;
using std::reverse_copy;
using std::rotate;
using std::rotate_copy;
using std::random_shuffle;

template<class RandomAccessIterator, class RandomNumberGenerator>
void random_shuffle(RandomAccessIterator first, RandomAccessIterator last,
		STD11_RV_REF(RandomNumberGenerator) rand)
{
	if (first == last)
	{
		return;
	}

	RandomNumberGenerator& r(rand.instance);
	for (RandomAccessIterator it = first + 1; it != last; ++it)
	{
		std::iter_swap(it, first + r(it - first + 1));
	}
}

// TODO implement
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

template <class InputIterator, class Predicate>
bool is_partitioned(InputIterator first, InputIterator last, Predicate pred)
{
	return none_of(find_if_not(first, last, pred), last, pred);
}

using std::partition;
using std::stable_partition;

template <class InputIterator, class OutputIterator1, class OutputIterator2,
	class Predicate>
pair<OutputIterator1, OutputIterator2>
partition_copy(InputIterator first, InputIterator last,
			OutputIterator1 out_true, OutputIterator2 out_false,
			Predicate pred)
{
	for (; first != last; ++first)
	{
		if (pred(*first))
		{
			*out_true++ = *first;
		}
		else
		{
			*out_false++ = *first;
		}
	}

	return ::std11::make_pair(out_true, out_false);
}

template <class ForwardIterator, class Predicate>
ForwardIterator partition_point(ForwardIterator first, ForwardIterator last,
		Predicate pred)
{
	typedef typename iterator_traits<ForwardIterator>::difference_type
			iterator_diff_type;
	iterator_diff_type n = std::distance(first, last);

	while (n > 0)
	{
		ForwardIterator it = first;
		iterator_diff_type step = n / 2;
		std::advance(it, step);
		if (pred(*it))
		{
			first = ++it;
			n -= step + 1;
		}
		else
		{
			n = step;
		}
	}
	return first;
}

using std::sort;
using std::stable_sort;
using std::partial_sort;
using std::partial_sort_copy;

template <class ForwardIterator>
ForwardIterator is_sorted_until(ForwardIterator first, ForwardIterator last);

template <class ForwardIterator, class Comparator>
ForwardIterator is_sorted_until(ForwardIterator first, ForwardIterator last,
		Comparator comp);

template <class ForwardIterator>
bool is_sorted(ForwardIterator first, ForwardIterator last)
{
	return is_sorted_until(first, last) == last;
}

template<class ForwardIterator, class Comparator>
bool is_sorted(ForwardIterator first, ForwardIterator last, Comparator comp)
{
	return is_sorted_until(first, last, comp) == last;
}

template <class ForwardIterator>
ForwardIterator is_sorted_until(ForwardIterator first, ForwardIterator last)
{
	typedef less<typename iterator_traits<ForwardIterator>::value_type>
		default_comparator_type;
	return is_sorted_until(first, last, default_comparator_type());
}

template <class ForwardIterator, class Comparator>
ForwardIterator is_sorted_until(ForwardIterator first, ForwardIterator last,
		Comparator comp)
{
	ForwardIterator it = first;
	if (it == last || ++it == last)
	{
		return last;
	}
	while (it != last && comp(*first, *it))
	{
		++first;
		++it;
	}

	return it;
}

using std::nth_element;
using std::lower_bound;
using std::upper_bound;
using std::equal_range;
using std::binary_search;
using std::merge;
using std::inplace_merge;
using std::set_union;
using std::set_intersection;
using std::set_difference;
using std::set_symmetric_difference;
using std::push_heap;
using std::pop_heap;
using std::make_heap;
using std::sort_heap;

template <class RandomAccessIterator>
RandomAccessIterator
is_heap_until(RandomAccessIterator first, RandomAccessIterator last);

template <class RandomAccessIterator, class Comparator>
RandomAccessIterator
is_heap_until(RandomAccessIterator first, RandomAccessIterator last,
			Comparator comp);

template <class RandomAccessIterator>
bool is_heap(RandomAccessIterator first, RandomAccessIterator last)
{
	return is_heap_until(first, last) == last;
}

template <class RandomAccessIterator, class Comparator>
bool is_heap(RandomAccessIterator first, RandomAccessIterator last,
		Comparator comp)
{
	return is_heap_until(first, last, comp) == last;
}

template <class RandomAccessIterator>
RandomAccessIterator
is_heap_until(RandomAccessIterator first, RandomAccessIterator last)
{
	typedef less<typename iterator_traits<RandomAccessIterator>::value_type>
		default_comparator_type;
	return is_heap_until(first, last, default_comparator_type());
}

template <class RandomAccessIterator, class Comparator>
RandomAccessIterator
is_heap_until(RandomAccessIterator first, RandomAccessIterator last,
			Comparator comp)
{
	RandomAccessIterator parent_node = first;
	RandomAccessIterator child_node = first;
	if (child_node == last || ++child_node == last)
	{
		return last;
	}

	bool advance_parent = false;
	while (child_node != last && comp(*child_node, *parent_node))
	{
		if (advance_parent)
		{
			++parent_node;
		}
		++child_node;
		advance_parent = !advance_parent;
	}

	return child_node;
}

using std::min;
using std::max;

template<class T, class Comparator>
pair<T const&, T const&> minmax(T const& a, T const& b, Comparator comp);

template<class T>
pair<T const&, T const&> minmax(T const& a, T const& b)
{
	return minmax(a, b, less<T>());
}

template<class T, class Comparator>
pair<T const&, T const&> minmax(T const& a, T const& b, Comparator comp)
{
	return comp(a, b)
			? std11::pair<T const&, T const&>(a, b)
			: std11::pair<T const&, T const&>(b, a);
}

//template<class T>
//pair<T, T> minmax(initializer_list<T> t);

//template<class T, class Compare>
//pair<T, T> minmax(initializer_list<T> t, Compare comp);

using std::min_element;
using std::max_element;

template<class ForwardIterator, class Comparator>
pair<ForwardIterator, ForwardIterator>
minmax_element(ForwardIterator first, ForwardIterator last, Comparator comp);

template<class ForwardIterator>
pair<ForwardIterator, ForwardIterator>
minmax_element(ForwardIterator first, ForwardIterator last)
{
	typedef less<typename iterator_traits<ForwardIterator>::value_type>
		default_comparator_type;
	return minmax_element(first, last, default_comparator_type());
}

template<class ForwardIterator, class Comparator>
pair<ForwardIterator, ForwardIterator>
minmax_element(ForwardIterator first, ForwardIterator last, Comparator comp)
{
	if (first == last)
	{
		return ::std11::make_pair(last, last);
	}

    ForwardIterator min_result = first;
	ForwardIterator max_result = first;

	++first;
	for (; first != last; ++first)
	{
		if (comp(*first, *min_result))
		{
			min_result = first;
		}
		else if (comp(*max_result, *first))
		{
			max_result = first;
		}
	}

	return ::std11::make_pair(min_result, max_result);
}

}  // namespace std11

#endif /* STDBP_STD11_ALGORITHM_HPP_ */
