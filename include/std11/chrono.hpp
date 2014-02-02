/*
 * chrono.hpp
 *
 *  Created on: 2013/01/11
 *      Author: hrkn
 */

#ifndef STDBP_STD11_CHRONO_HPP_
#define STDBP_STD11_CHRONO_HPP_

#include <stdint.h>

#include "std11/_config.hpp"
#include "std11/ratio.hpp"

namespace std11
{

namespace chrono
{

namespace chrono_detail
{
void lib_init(void);

// clock_gettimeの動的ロード

}  // namespace chrono_detail

/// duration
template<typename Rep, typename Period = ratio<1> >
struct duration
{
	typedef Rep rep;
	typedef Period period;

	duration& operator=(const duration& rhs);
	duration operator+(void) const;
	duration operator-(void) const;
	duration& operator++();
	duration operator++(int);
	duration& operator--();
	duration operator--(int);
	duration& operator+=(const duration& rhs);
	duration& operator-=(const duration& rhs);
	duration& operator*=(const rep& r);
	duration& operator/=(const rep& r);
	duration& operator%=(const rep& r);
	duration& operator%=(const duration& rhs);
};

/// nanoseconds
typedef duration<int64_t,     nano> nanoseconds;
/// microseconds
typedef duration<int64_t,    micro> microseconds;
/// milliseconds
typedef duration<int64_t,    milli> milliseconds;
/// seconds
typedef duration<int64_t          > seconds;
/// minutes
typedef duration<int,   ratio<60> > minutes;
/// hours
typedef duration<int, ratio<3600> > hour;

}  // namespace chrono

}  // namespace std11

#endif /* STDBP_STD11_CHRONO_HPP_ */
