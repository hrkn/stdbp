/*
 * cstddef.hpp
 *
 *  Created on: 2014/03/07
 *      Author: Haruki Nakayama
 */

#ifndef STDBP_STD11_CSTDDEF_HPP_
#define STDBP_STD11_CSTDDEF_HPP_

#include <cstddef>

#include "std11/language_extension/nullptr.hpp"

#if !defined(offsetof) || defined(STDBP_FORCE_DEFINE_ORIGINAL_OFFSETOF)
#undef offsetof
#define STDBP_HAS_ORIGINAL_OFFSETOF
#define offsetof(type, offset) \
	(reinterpret_cast<size_t>(&reinterpret_cast<type const* const>(NULL)->offset))
#endif

namespace std11
{

using std::ptrdiff_t;
using std::size_t;

}  // namespace std11

#endif /* STDBP_STD11_CSTDDEF_HPP_ */
