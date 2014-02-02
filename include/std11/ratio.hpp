/*
 * ratio.hpp
 *
 *  Created on: 2013/01/11
 *      Author: hrkn
 */
#ifndef STDBP_STD11_RATIO_HPP_
#define STDBP_STD11_RATIO_HPP_

#include <stdint.h>

#include "std11/_config.hpp"
#include "std11/type_traits.hpp"

namespace std11
{

namespace static_calculation
{

template <intmax_t Pn>
struct sign: integral_constant<intmax_t, (Pn < 0) ? -1 : 1> {};

template<intmax_t Pn>
struct abs: integral_constant<intmax_t, Pn * sign<Pn>::value> {};

template<intmax_t Pn, intmax_t Qn>
struct gcd;

template<intmax_t Pn, intmax_t Qn>
struct gcd: gcd<Qn, (Pn % Qn)> {};

template<intmax_t Pn>
struct gcd<Pn, 0>: integral_constant<intmax_t, abs<Pn>::value> {};

template<intmax_t Qn>
struct gcd<0, Qn>: integral_constant<intmax_t, abs<Qn>::value> {};

}  // namespace static_calc

template <intmax_t N, intmax_t D = 1>
struct ratio
{
	static intmax_t const num =
			N * static_calculation::sign<D>::value
			  / static_calculation::gcd<N, D>::value;
	static intmax_t const den =
			static_calculation::abs<D>::value / static_calculation::gcd<N, D>::value;

	// non-standard constant
	static double const real_value;

	operator double(void)
	{
		return static_cast<double>(num) / static_cast<double>(den);
	}
};

template <intmax_t N, intmax_t D>
double const ratio<N, D>::real_value = static_cast<double>(N) / D;


typedef ratio<                  1  , 1000000000000000000LL> atto;
typedef ratio<                  1  , 1000000000000000LL>    femto;
typedef ratio<                  1  , 1000000000000LL>       pico;
typedef ratio<                  1  , 1000000000>            nano;
typedef ratio<                  1  , 1000000>               micro;
typedef ratio<                  1  , 1000>                  milli;
typedef ratio<                  1  , 100>                   centi;
typedef ratio<                  1  , 10>                    deci;
typedef ratio<                 10  , 1>                     deca;
typedef ratio<                100  , 1>                     hecto;
typedef ratio<               1000  , 1>                     kilo;
typedef ratio<            1000000  , 1>                     mega;
typedef ratio<         1000000000  , 1>                     giga;
typedef ratio<      1000000000000LL, 1>                     tera;
typedef ratio<   1000000000000000LL, 1>                     peta;
typedef ratio<1000000000000000000LL, 1>                     exa;

template <typename R1, typename R2>
struct ratio_add : public ratio <
	R1::num * R2::den + R2::num * R1::den,
	R1::den * R2::den> {};

template <typename R1, typename R2>
struct ratio_subtract : public ratio <
	R1::num * R2::den - R2::num * R1::den,
	R1::den * R2::den > {};

template <typename R1, typename R2>
struct ratio_multiply : public ratio <
	R1::num * R2::num,
	R1::den * R2::den > {};

template <typename R1, typename R2>
struct ratio_divide : public ratio <
	R1::num * R2::den,
	R2::num * R1::den > {};

// TODO seperate non-standard typedefs to other file
typedef ratio<1024>                kibi;
typedef ratio_multiply<kibi, kibi> mebi;
typedef ratio_multiply<mebi, kibi> gibi;
typedef ratio_multiply<gibi, kibi> tebi;
typedef ratio_multiply<tebi, kibi> pebi;
typedef ratio_multiply<pebi, kibi> exbi;

}  // namespace std11

#endif /* STDBP_STD11_RATIO_HPP_ */
