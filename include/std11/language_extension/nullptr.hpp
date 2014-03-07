/*
 * nullptr.hpp
 *
 *  Created on: 2013/06/03
 *      Author: hrkn
 */

#ifndef STDBP_STD11_LANGUAGE_EXTENSION_NULLPTR_HPP_
#define STDBP_STD11_LANGUAGE_EXTENSION_NULLPTR_HPP_

#include "std11/_config.hpp"

#if !STDBP_CPP11_ENABLED

class nullptr_t
{
public:
	template <typename T>
	operator T*() const // 任意の非メンバ型のヌルポインタや、
	{
		return 0;
	}

	template<class C, class T>
	operator T C::*() const   // 任意のメンバ型のヌルポインタに変換可能であって、
	{
		return 0;
	}

private:
	void operator&() const;  // アドレスを取得することができない。

};

nullptr_t const nullptr = {};

#endif

#endif /* STDBP_STD11_LANGUAGE_EXTENSION_NULLPTR_HPP_ */
