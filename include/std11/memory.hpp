/*
 * memory.hpp
 *
 *  Created on: 2013/03/01
 *      Author: hrkn
 */

#ifndef STDBP_STD11_MEMORY_HPP_
#define STDBP_STD11_MEMORY_HPP_

#include <memory>

namespace std11
{

template<class T>
T* addressof(T& r) throw ()
{
	return reinterpret_cast<T*>(&const_cast<char&>(
			reinterpret_cast<const volatile char&>(r)));
}

}  // namespace std11

#endif /* STDBP_STD11_MEMORY_HPP_ */
