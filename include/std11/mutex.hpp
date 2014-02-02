/*
 * mutex.hpp
 *
 *  Created on: 2013/02/12
 *      Author: hrkn
 */
#ifndef STDBP_STD11_MUTEX_HPP_
#define STDBP_STD11_MUTEX_HPP_

#include <stddef.h>
#include <pthread.h>

#include <limits>
#include <memory>

#include "std11/_config.hpp"
#include "std11/chrono.hpp"
#include "std11/utility.hpp"
#include "std11/thread.hpp"
#include "std11/functional.hpp"
#include "std11/internal/noncopyable.hpp"
#include "std11/internal/once_caller.hpp"

namespace std11
{

struct defer_lock_t
{
}const defer_lock = {};

struct try_to_lock_t
{
}const try_to_lock = {};

struct adopt_lock_t
{
}const adopt_lock = {};

//
//  ==== lock_guard ====
//
template<class Mutex>
class lock_guard: private noncopyable
{
public:
	typedef Mutex mutex_type;

private:
	mutex_type& syncronizer_;

public:
	explicit lock_guard(mutex_type& m) :
			syncronizer_(m)
	{
		syncronizer_.lock();
	}

	lock_guard(mutex_type& m, adopt_lock_t) :
			syncronizer_(m)
	{
	}

	~lock_guard(void)
	{
		syncronizer_.unlock();
	}
};

//
//  ==== unique_lock ====
//
template<class Mutex>
class unique_lock: private noncopyable
{
public:
	typedef Mutex mutex_type;

private:
	mutex_type* syncronizer_;
	bool locked_;

public:
	explicit unique_lock(Mutex& m) :
			syncronizer_(&m), locked_(false)
	{
		lock();
	}

	unique_lock(mutex_type& m, defer_lock_t) throw () :
			syncronizer_(&m), locked_(false)
	{
	}

	unique_lock(mutex_type& m, try_to_lock_t) :
			syncronizer_(&m), locked_(m.try_lock())
	{
	}

	unique_lock(mutex_type& m, adopt_lock_t) :
			syncronizer_(&m), locked_(true)
	{
	}

//	template<class Clock, class Duration>
//	unique_lock(mutex_type& m, chrono::time_point<Clock, Duration> const& abs_time) :
//			syncronizer_(&m), locked_(m.try_lock_until(abs_time))
//	{
//	}

//	template<class Rep, class Period>
//	unique_lock(mutex_type& m, chrono::duration<Rep, Period> const& rel_time) :
//			syncronizer_(&m), locked_(m.try_lock_for(rel_time))
//	{
//	}

	unique_lock(STD11_RV_REF(unique_lock) u) throw () :
			syncronizer_(NULL), locked_(false)
	{
		swap(u.instance);
	}

	~unique_lock(void)
	{
		if (owns_lock())
		{
			unlock();
		}
	}

	unique_lock& operator=(STD11_RV_REF(unique_lock) u) throw ()
	{
		if (owns_lock())
		{
			unlock();
		}

		unique_lock(u).swap(*this);

		return *this;
	}

	void lock(void)
	{
		if (syncronizer_ == NULL)
		{
			// throw system_error(...);
		}
		else if (owns_lock())
		{
			// throw system_error(...);
		}
		else
		{
			syncronizer_->lock();
			locked_ = true;
		}
	}

	bool try_lock(void)
	{
		if (syncronizer_ == NULL)
		{
			// throw system_error(...);
		}
		else if (owns_lock())
		{
			// throw system_error(...);
		}

		locked_ = syncronizer_->try_lock();
		return locked_;
	}

//	template<class Rep, class Period>
//	bool try_lock_for(chrono::duration<Rep, Period> const& rel_time);
//	{
//		return false;
//	}

//	template<class Clock, class Duration>
//	bool try_lock_until(chrono::time_point<Clock, Duration> const& abs_time);
//	{
//		return false;
//	}

	void unlock(void)
	{
		if (owns_lock())
		{
			syncronizer_->unlock();
			locked_ = false;
		}
		else
		{
			// throw system_error(...);
		}
	}

	void swap(unique_lock& u) throw ()
	{
		std::swap(syncronizer_, u.syncronizer_);
		std::swap(locked_, u.locked_);
	}

	mutex_type* release(void) throw ()
	{
		mutex_type* ret_pointer = syncronizer_;
		syncronizer_ = NULL;
		locked_ = false;

		return ret_pointer;
	}

	bool owns_lock() const throw ()
	{
		return locked_;
	}

	operator bool() const throw ()
	{
		return owns_lock();
	}

	mutex_type* mutex() const throw ()
	{
		return syncronizer_;
	}
};

template<class Mutex>
void swap(unique_lock<Mutex>& x, unique_lock<Mutex>& y) throw ()
{
	x.swap(y);
}

//
//  ==== mutex ====
//
class mutex: private noncopyable
{
	friend class condition_variable;

	typedef pthread_mutex_t native_type;
	native_type native_mutex_;

public:
	typedef native_type* native_handle_type;

	mutex(void) throw ()
	{
		pthread_mutex_init(&native_mutex_, NULL);
	}

	~mutex(void) throw ()
	{
		pthread_mutex_destroy(&native_mutex_);
	}

	void lock(void)
	{
		pthread_mutex_lock(&native_mutex_);
	}

	bool try_lock(void) throw ()
	{
		return (pthread_mutex_trylock(&native_mutex_) == 0);
	}

	void unlock(void)
	{
		pthread_mutex_unlock(&native_mutex_);
	}

	native_handle_type native_handle(void) throw ()
	{
		return &native_mutex_;
	}

};

class lock_ownership_counter
{
	// TODO pthread_t -> thread::id
	thread::id owner_;
	unsigned counter_;
	mutex mutable synchronizer_;

protected:
	lock_ownership_counter(void) :
			owner_(), counter_(0), synchronizer_()
	{
	}

	~lock_ownership_counter()
	{
	}

	unsigned increment()
	{
		lock_guard<mutex> l(synchronizer_);
		if (counter_ == std::numeric_limits<unsigned>::max())
		{
			// TODO throw exception
		}
		return ++counter_;
	}

	unsigned decrement()
	{
		lock_guard<mutex> l(synchronizer_);
		if (counter_ == std::numeric_limits<unsigned>::min())
		{
			// TODO throw exception
		}
		return --counter_;
	}

	unsigned count() const
	{
		lock_guard<mutex> l(synchronizer_);
		return counter_;
	}

	bool owned_by_this_thread()
	{
		lock_guard<mutex> l(synchronizer_);
		return owner_ == this_thread::get_id();
	}

	bool own(void)
	{
		lock_guard<mutex> l(synchronizer_);

		if (owner_ != thread::id())
		{
			return false;
		}
		else
		{
			owner_ = this_thread::get_id();
			return true;
		}
	}

	bool disown(void)
	{
		lock_guard<mutex> l(synchronizer_);

		if (owner_ != this_thread::get_id())
		{
			return false;
		}
		else
		{
			owner_ = thread::id();
			return true;
		}
	}
};

//
//  ==== recursive_mutex ====
//
class recursive_mutex: private mutex, private lock_ownership_counter
{
	friend class condition_variable;

	typedef pthread_mutex_t native_type;

public:
	typedef native_type* native_handle_type;

	recursive_mutex(void) throw () :
			mutex(), lock_ownership_counter()
	{
	}

	~recursive_mutex(void)
	{
	}

	void lock(void)
	{
		while (true)
		{
			if (owned_by_this_thread())
			{
				increment();
				break;
			}
			mutex::lock();
			own();
		}
	}

	bool try_lock(void)
	{
		if (owned_by_this_thread())
		{
			increment();
			return true;
		}

		if (mutex::try_lock())
		{
			own();
			increment();
			return true;
		}
		else
		{
			return false;
		}
	}

	void unlock(void)
	{
		if (owned_by_this_thread())
		{
			if (decrement() == 0)
			{
				disown();
				mutex::unlock();
			}
		}
		else
		{
			// illegal state!
		}
	}

	native_handle_type native_handle()
	{
		return mutex::native_handle();
	}
};

//
//  ==== timed_mutex ====
//
class timed_mutex: private mutex
{
	friend class condition_variable;

	typedef pthread_mutex_t native_type;

public:
	typedef native_type* native_handle_type;

	timed_mutex(void) :
			mutex()
	{
	}

	~timed_mutex(void)
	{
	}

	void lock(void)
	{
		mutex::lock();
	}

	bool try_lock(void) throw ()
	{
		return mutex::try_lock();
	}

	bool try_lock_for(int rel_time_milliseconds);

//	template<class Rep, class Period>
//	bool try_lock_for(const chrono::duration<Rep, Period>& rel_time);
//
//	template<class Clock, class Duration>
//	bool try_lock_until(const chrono::time_point<Clock, Duration>& abs_time);

	void unlock(void)
	{
		mutex::unlock();
	}

	native_handle_type native_handle()
	{
		return mutex::native_handle();
	}

};

//
//  ==== recursive_timed_mutex ====
//
class recursive_timed_mutex: private timed_mutex, private lock_ownership_counter
{
public:
	typedef pthread_mutex_t* native_handle_type;

	recursive_timed_mutex(void) :
			timed_mutex(), lock_ownership_counter()
	{
	}
	~recursive_timed_mutex(void)
	{
	}

	void lock(void)
	{
		timed_mutex::lock();
	}

	bool try_lock(void) throw ()
	{
		return timed_mutex::try_lock();
	}

	bool try_lock_for(int rel_time_milliseconds);

//	template<class Rep, class Period>
//	bool try_lock_for(chrono::duration<Rep, Period> const& rel_time);
//
//	template<class Clock, class Duration>
//	bool try_lock_until(chrono::time_point<Clock, Duration> const& abs_time);

	void unlock(void)
	{
		timed_mutex::unlock();
	}

	native_handle_type native_handle()
	{
		return timed_mutex::native_handle();
	}
};

//
//  ==== call_once ====
//
struct once_flag;
namespace call_once_detail
{
	static void init_routine(once_flag& flag, detail::runner_base* runner);
}

struct once_flag: private noncopyable
{
	friend void call_once_detail::init_routine(once_flag& flag, detail::runner_base* runner);
	pthread_once_t once_control;
	once_flag() throw () :
			once_control(PTHREAD_ONCE_INIT)
	{
	}
};

namespace call_once_detail
{
// TODO seperate compilation unit
static __thread detail::runner_base* once_callable = NULL;

// TODO seperate compilation unit
static void init_routine_core(void)
{
	once_callable->run();
}

// TODO seperate compilation unit
static void init_routine(once_flag& flag, detail::runner_base* runner)
{
	if (runner == NULL)
	{
		// TODO throw system_error(...);
	}

	try
	{
		call_once_detail::once_callable = runner;
		pthread_once(&flag.once_control, call_once_detail::init_routine_core);
	}
	catch (...)
	{
		flag.once_control = PTHREAD_ONCE_INIT;
		throw;
	}
}

}  // namespace call_once_detail

template<typename Func>
void call_once(once_flag& flag, Func const& func)
{
	std::auto_ptr<detail::runner_base> callable(detail::make_runner(func));
	call_once_detail::init_routine(flag, callable.get());
}

template<typename Func, typename A1>
void call_once(once_flag& flag, Func const& func, A1 const& a1)
{
	std::auto_ptr<detail::runner_base> callable(detail::make_runner(bind(func, a1)));
	call_once_detail::init_routine(flag, callable.get());
}

template<typename Func, typename A1, typename A2>
void call_once(once_flag& flag, Func const& func, A1 const& a1, A2 const& a2)
{
	std::auto_ptr<detail::runner_base> callable(detail::make_runner(bind(func, a1, a2)));
	call_once_detail::init_routine(flag, callable.get());
}

template<typename Func, typename A1, typename A2, typename A3>
void call_once(once_flag& flag, Func const& func, A1 const& a1, A2 const& a2,
		A3 const& a3)
{
	std::auto_ptr<detail::runner_base> callable(detail::make_runner(bind(func, a1, a2, a3)));
	call_once_detail::init_routine(flag, callable.get());
}

template<typename Func, typename A1, typename A2, typename A3, typename A4>
void call_once(once_flag& flag, Func const& func, A1 const& a1, A2 const& a2,
		A3 const& a3, A4 const& a4)
{
	std::auto_ptr <detail::runner_base>
			callable(detail::make_runner(bind(func, a1, a2, a3, a4)));
	call_once_detail::init_routine(flag, callable.get());
}

template<typename Func, typename A1, typename A2, typename A3, typename A4,
	typename A5>
void call_once(once_flag& flag, Func const& func, A1 const& a1, A2 const& a2,
		A3 const& a3, A4 const& a4, A5 const& a5)
{
	std::auto_ptr <detail::runner_base>
			callable(detail::make_runner(bind(func, a1, a2, a3, a4, a5)));
	call_once_detail::init_routine(flag, callable.get());
}

template<typename Func, typename A1, typename A2, typename A3, typename A4,
	typename A5, typename A6>
void call_once(once_flag& flag, Func const& func, A1 const& a1, A2 const& a2,
		A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6)
{
	std::auto_ptr <detail::runner_base>
			callable(detail::make_runner(bind(func, a1, a2, a3, a4, a5, a6)));
	call_once_detail::init_routine(flag, callable.get());
}

template<typename Func, typename A1, typename A2, typename A3, typename A4,
	typename A5, typename A6, typename A7>
void call_once(once_flag& flag, Func const& func, A1 const& a1, A2 const& a2,
		A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7)
{
	std::auto_ptr <detail::runner_base>
			callable(detail::make_runner(bind(func, a1, a2, a3, a4, a5, a6, a7)));
	call_once_detail::init_routine(flag, callable.get());
}

template<typename Func, typename A1, typename A2, typename A3, typename A4,
	typename A5, typename A6, typename A7, typename A8>
void call_once(once_flag& flag, Func const& func, A1 const& a1, A2 const& a2,
		A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7,
		A8 const& a8)
{
	std::auto_ptr <detail::runner_base>
			callable(detail::make_runner(bind(func, a1, a2, a3, a4, a5, a6, a7, a8)));
	call_once_detail::init_routine(flag, callable.get());
}

template<typename Func, typename A1, typename A2, typename A3, typename A4,
	typename A5, typename A6, typename A7, typename A8, typename A9>
void call_once(once_flag& flag, Func const& func, A1 const& a1, A2 const& a2,
		A3 const& a3, A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7,
		A8 const& a8, A9 const& a9)
{
	std::auto_ptr <detail::runner_base>
			callable(
					detail::make_runner(
							bind(func, a1, a2, a3, a4, a5, a6, a7, a8, a9)));
	call_once_detail::init_routine(flag, callable.get());
}

}  // namespace std11

#endif /* STDBP_STD11_MUTEX_HPP_ */
