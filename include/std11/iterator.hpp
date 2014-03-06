/*
 * iterator.hpp
 *
 *  Created on: 2014/02/24
 *      Author: Haruki Nakayama
 */

#ifndef STDBP_STD11_ITERATOR_HPP_
#define STDBP_STD11_ITERATOR_HPP_

#include <iterator>

namespace std11
{

using std::iterator_traits;
using std::iterator;
using std::input_iterator_tag;
using std::output_iterator_tag;
using std::forward_iterator_tag;
using std::bidirectional_iterator_tag;
using std::random_access_iterator_tag;
using std::advance;
using std::distance;

}  // namespace std11


#endif /* STDBP_STD11_ITERATOR_HPP_ */
