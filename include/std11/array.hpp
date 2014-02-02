/*
 * array.hpp
 *
 *  Created on: 2013/02/22
 *      Author: hrkn
 */

#ifndef STDBP_STD11_ARRAY_HPP_
#define STDBP_STD11_ARRAY_HPP_

#include <cstddef>

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include "std11/type_traits.hpp"

namespace std11
{

template<typename T, std::size_t N>
struct array
{
	T data_[N];

	typedef T& reference;
	typedef T const& const_reference;
	typedef T* iterator;
	typedef T const* const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T const* const_pointer;
	typedef T value_type;

	reference at(size_type n)
	{
		if (n > N)
		{
			throw std::out_of_range();
		}
		return data_[n];
	}

	const_reference at(size_type n) const
	{
		if (n > N)
		{
			throw std::out_of_range();
		}
		return data_[n];
	}

	reference operator[](size_type n)
	{
		return data_[n];
	}

	const_reference operator[](size_type n) const
	{
		return data_[n];
	}

	// TODO erase by specialization if N == 0
	reference front()
	{
		return data_[0];
	}

	// TODO erase by specialization if N == 0
	const_reference front() const
	{
		return data_[0];
	}

	// TODO erase by specialization if N == 0
	reference back()
	{
		return data_[N - 1];
	}

	// TODO erase by specialization if N == 0
	const_reference back() const
	{
		return data_[N - 1];
	}

	pointer data() throw ()
	{
		return &data_[0];
	}

	const_pointer data() const throw ()
	{
		return &data_[0];
	}

	iterator begin() throw ()
	{
		return iterator(data());
	}

	const_iterator begin() const throw ()
	{
		return const_iterator(data());
	}

	iterator end() throw ()
	{
		return iterator(data() + N);
	}

	const_iterator end() const throw ()
	{
		return const_iterator(data() + N);
	}

	const_iterator cbegin() const throw ()
	{
		return const_iterator(data());
	}

	const_iterator cend() const throw ()
	{
		return const_iterator(data() + N);
	}

	reverse_iterator rbegin() throw ()
	{
		return reverse_iterator(end());
	}

	const_reverse_iterator rbegin() const throw ()
	{
		return const_reverse_iterator(end());
	}

	reverse_iterator rend() throw ()
	{
		return reverse_iterator(begin());
	}

	const_reverse_iterator rend() const throw ()
	{
		return const_reverse_iterator(begin());
	}

	const_reverse_iterator crbegin() const throw ()
	{
		return const_reverse_iterator(end());
	}

	const_reverse_iterator crend() const throw ()
	{
		return const_reverse_iterator(begin());
	}

	bool empty() const throw ()
	{
		return N == 0;
	}

	size_type size() const throw ()
	{
		return N;
	}

	size_type max_size() const throw ()
	{
		return N;
	}

	void fill(T const& u)
	{
		std::fill_n(begin(), N, u);
	}

	// TODO override with 'noexcept specification' by specialization if N == 0
	void swap(array& other)
	{
		swap_ranges(begin(), end(), other.begin());
	}
};

template<typename T> class tuple_size;

template<typename T, size_t N>
struct tuple_size<array<T, N> > : integral_constant<size_t, N>
{
};

template<size_t I, typename T> class tuple_element;

template<size_t I, typename T, size_t N>
struct tuple_element<I, array<T, N> >
{
//	static_assert(I < N, "Requires (I < N)");
	typedef T type;
};

template <size_t I, class T, size_t N>
T& get(array<T, N>& x) throw ()
{
	//static_assert(I < N, "Requires (I < N)");
	return x[I];
}

//template <size_t I, class T, size_t N>
//T&& get(array<T, N>&& x) throw ()
//{
//	//static_assert(I < N, "Requires (I < N)");
//	return x[I];
//}

template <size_t I, class T, size_t N>
const T& get(array<T, N> const& x) throw ()
{
	//static_assert(I < N, "Requires (I < N)");
	return x[I];
}

}  // namespace std11

#endif /* STDBP_STD11_ARRAY_HPP_ */
