/*
 * noncopyable.hpp
 *
 *  Created on: 2013/02/19
 *      Author: hrkn
 */

#ifndef STDBP_STD11_INTERNAL_NONCOPYABLE_HPP_
#define STDBP_STD11_INTERNAL_NONCOPYABLE_HPP_

namespace std11
{

class noncopyable
{
protected:
	noncopyable(void)
	{
	}
	~noncopyable(void)
	{
	}

private:
	noncopyable(noncopyable const&);
	noncopyable& operator=(noncopyable const&);
};

}  // namespace std11

#endif /* STDBP_STD11_INTERNAL_NONCOPYABLE_HPP_ */
