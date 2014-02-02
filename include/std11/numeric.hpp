/*
 * numeric.hpp
 *
 *  Created on: 2013/04/04
 *      Author: hrkn
 */

#ifndef STDBP_STD11_NUMERIC_HPP_
#define STDBP_STD11_NUMERIC_HPP_

#include <numeric>

namespace std11
{

template<class ForwardIterator, class T>
void iota(ForwardIterator first, ForwardIterator last, T value)
{
	while (first != last)
	{
		*(first++) = value++;
	}
}

}  // namespace std11

#endif /* STDBP_STD11_NUMERIC_HPP_ */
