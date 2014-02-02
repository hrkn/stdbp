/*
 * future.hpp
 *
 *  Created on: 2013/05/08
 *      Author: hrkn
 */

#ifndef STDBP_STD11_FUTURE_HPP_
#define STDBP_STD11_FUTURE_HPP_

#include <iosfwd>
#include <stdexcept>

#include "std11/system_err.hpp"
#include "std11/language_extension/enum_class.hpp"
#include "std11/internal/noncopyable.hpp"

namespace std11
{
int const FUTURE_ENUM_PREFIX = 0x1102u;

struct future_errc: enum_class<future_errc, unsigned>
{
	future_errc(unsigned v): enum_class<future_errc, unsigned>(v) {}

	static future_errc const
		broken_promise,
		future_already_retrieved,
		promise_already_satisfied,
		no_state;
};

struct launch: public enum_class<launch, unsigned>
{
	launch(int v): enum_class<launch, unsigned>(v) {}

	static launch const
		async,
		deferred;
};

struct future_status: public enum_class<future_status, unsigned>
{
	future_status(int v): enum_class<future_status, unsigned>(v) {}

	static future_status const
		ready,
		timeout,
		deffered;
};

// TODO separate compilation unit
future_errc const future_errc::broken_promise(0);
future_errc const future_errc::future_already_retrieved(1);
future_errc const future_errc::promise_already_satisfied(2);
future_errc const future_errc::no_state(3);

launch const launch::async(4);
launch const launch::deferred(5);

future_status const future_status::ready(6);
future_status const future_status::timeout(7);
future_status const future_status::deffered(8);

template<>
struct is_error_code_enum<future_errc> : public is_enum<future_errc>
{
};

//error_code make_error_code(future_errc e) throw ()
//{
//	return error_code(static_cast<int>(e), future_category());
//}
//
//error_condition make_error_condition(future_errc e) throw ()
//{
//	return error_condition(static_cast<int>(e), future_category());
//}
//
//const error_category& future_category() throw ()
//{
//	return error_category();
//}

class future_error: public std::logic_error
{
public:
	future_error(error_code ec);

	const error_code& code() const throw ();
	virtual const char* what() const throw ();
};

template<class R>
class promise;

template<class R>
class future;

template<class R>
class shared_future;

template<class >
class packaged_task;

//template<class R, class ... ArgTypes>
//class packaged_task<R(ArgTypes...)> ;
//
//template<class F, class ... Args>
//future<typename result_of<F(Args...)>::type>
//async(F&& f, Args&&... args);
//
//template<class F, class ... Args>
//future<typename result_of<F(Args...)>::type>
//async(launch policy, F&& f, Args&&... args);

}  // namespace std11

#endif /* STDBP_STD11_FUTURE_HPP_ */
