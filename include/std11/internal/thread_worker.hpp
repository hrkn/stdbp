/*
 * thread_worker.hpp
 *
 *  Created on: 2013/02/20
 *      Author: hrkn
 */

#ifndef STDBP_STD11_INTERNAL_THREAD_WORKER_HPP_
#define STDBP_STD11_INTERNAL_THREAD_WORKER_HPP_

#include "std11/type_traits.hpp"

namespace std11
{

namespace detail {

struct runner_base
{
	virtual ~runner_base()
	{
	}

	virtual void run() = 0;
};

template<typename Proc>
class runner: public runner_base
{
	Proc procedure_;

public:
	runner(Proc const& p) :
			procedure_(p)
	{
	}

	virtual void run()
	{
		procedure_();
	}
};

template<typename Func>
static inline runner_base* make_runner(Func const& f)
{
	// Funcの型が非ポインタな関数型だった場合、自動で関数ポインタ型に変換する
	typedef typename conditional<
		is_function<Func>::value,
		typename decay<Func>::type,
		Func
	>::type func_type;
	func_type const& f_ = f;

	return new runner<func_type>(f_);
}


inline void* run(void* arg)
{
	if (arg == NULL)
	{
		return reinterpret_cast<void*>(-1);
	}

	static_cast<runner_base*>(arg)->run();

	return NULL;
}

}  // namespace detail

}  // namespace std11

#endif /* STDBP_STD11_INTERNAL_THREAD_WORKER_HPP_ */
