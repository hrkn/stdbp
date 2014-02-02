/*
 * enum_class.hpp
 *
 *  Created on: 2013/05/08
 *      Author: hrkn
 */

#ifndef STDBP_STD11_LANGUAGE_EXTENSION_ENUM_CLASS_HPP_
#define STDBP_STD11_LANGUAGE_EXTENSION_ENUM_CLASS_HPP_

#include <iosfwd>

namespace std11
{

template<typename Derived, typename Integer = int>
class enum_class
{
	Integer v_;

protected:
	enum_class(Integer v) :
		v_(v)
	{
	}

	enum_class(enum_class const& src) :
		v_(src.v_)
	{
	}

public:
	operator Integer(void) const { return v_; }

	friend std::ostream& operator<<(std::ostream& os, Derived const& arg)
	{
		return os << arg.v_;
	}

	friend bool operator==(Derived const& lhs, Derived const& rhs)
	{
		return lhs.v_ == rhs.v_;
	}

	friend bool operator!=(Derived const& lhs, Derived const& rhs)
	{
		return !(lhs == rhs);
	}
};

}  // namespace std11

#endif /* STDBP_STD11_LANGUAGE_EXTENSION_ENUM_CLASS_HPP_ */
