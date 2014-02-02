/*
 * thread.hpp
 *
 *  Created on: 2013/01/11
 *      Author: hrkn
 */

#ifndef STDBP_STD11_THREAD_H_
#define STDBP_STD11_THREAD_H_

#include <sched.h>
#include <pthread.h>
#include <unistd.h>

#include <memory>

#include "std11/_config.hpp"
#include "std11/functional.hpp"
#include "std11/utility.hpp"
#include "std11/internal/thread_worker.hpp"
#include "std11/internal/noncopyable.hpp"

namespace std11
{

class thread: private noncopyable
{
public:
	typedef pthread_t native_handle_type;

	class id
	{
		friend class thread;
		friend class hash<thread::id>;

		native_handle_type native_thread_id_;

	public:
		id() throw () :
				native_thread_id_()
		{
		}

		explicit id(native_handle_type native_id) throw () :
				native_thread_id_(native_id)
		{
		}

	private:
		friend bool operator==(thread::id lhs, thread::id rhs) throw ()
		{
			return pthread_equal(lhs.native_thread_id_, rhs.native_thread_id_);
		}

		friend bool operator!=(thread::id lhs, thread::id rhs) throw ()
		{
			return !(lhs == rhs);
		}

		friend bool operator<(thread::id lhs, thread::id rhs) throw ()
		{
			return lhs.native_thread_id_ < rhs.native_thread_id_;
		}
	};

private:
	id id_;

	// TODO must be held by shared_ptr and should be shared with runner thread
	//      to avoid segmentation fault caused by "rapid instance destruction"
	std::auto_ptr<detail::runner_base> procedure_;

	void start_thread(detail::runner_base* rp)
	{
		procedure_.reset(rp);
		id new_id;
		if (pthread_create(&new_id.native_thread_id_, NULL, &detail::run,
				procedure_.get()) == 0)
		{
			id_ = new_id;
		}
		else
		{
			// throw std11::system_error(...);
		}
	}

public:
	thread(void) throw ()
	{
	}

	template<typename Func>
	explicit thread(Func const& func)
	{
		start_thread(detail::make_runner(func));
	}

	template<typename Func, typename A1>
	thread(Func const& func, A1 const& a1)
	{
		start_thread(detail::make_runner(bind(func, a1)));
	}

	template<typename Func, typename A1, typename A2>
	thread(Func const& func, A1 const& a1, A2 const& a2)
	{
		start_thread(detail::make_runner(bind(func, a1, a2)));
	}

	template<typename Func, typename A1, typename A2, typename A3>
	thread(Func const& func, A1 const& a1, A2 const& a2, A3 const& a3)
	{
		start_thread(detail::make_runner(bind(func, a1, a2, a3)));
	}

	template<typename Func, typename A1, typename A2, typename A3, typename A4>
	thread(Func const& func, A1 const& a1, A2 const& a2, A3 const& a3,
			A4 const& a4)
	{
		start_thread(detail::make_runner(bind(func, a1, a2, a3, a4)));
	}

	template<typename Func, typename A1, typename A2, typename A3, typename A4,
			typename A5>
	thread(Func const& func, A1 const& a1, A2 const& a2, A3 const& a3,
			A4 const& a4, A5 const& a5)
	{
		start_thread(detail::make_runner(bind(func, a1, a2, a3, a4, a5)));
	}

	template<typename Func, typename A1, typename A2, typename A3, typename A4,
			typename A5, typename A6>
	thread(Func const& func, A1 const& a1, A2 const& a2, A3 const& a3,
			A4 const& a4, A5 const& a5, A6 const& a6)
	{
		start_thread(detail::make_runner(bind(func, a1, a2, a3, a4, a5, a6)));
	}

	template<typename Func, typename A1, typename A2, typename A3, typename A4,
			typename A5, typename A6, typename A7>
	thread(Func const& func, A1 const& a1, A2 const& a2, A3 const& a3,
			A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7)
	{
		start_thread(detail::make_runner(bind(func, a1, a2, a3, a4, a5, a6, a7)));
	}

	template<typename Func, typename A1, typename A2, typename A3, typename A4,
			typename A5, typename A6, typename A7, typename A8>
	thread(Func const& func, A1 const& a1, A2 const& a2, A3 const& a3,
			A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7,
			A8 const& a8)
	{
		start_thread(detail::make_runner(bind(func, a1, a2, a3, a4, a5, a6, a7, a8)));
	}

	template<typename Func, typename A1, typename A2, typename A3, typename A4,
			typename A5, typename A6, typename A7, typename A8, typename A9>
	thread(Func const& func, A1 const& a1, A2 const& a2, A3 const& a3,
			A4 const& a4, A5 const& a5, A6 const& a6, A7 const& a7,
			A8 const& a8, A9 const& a9)
	{
		start_thread(
				detail::make_runner(bind(func, a1, a2, a3, a4, a5, a6, a7, a8, a9)));
	}

	thread(STD11_RV_REF(thread) source) :
			id_(), procedure_()
	{
		// 前提条件としてムーブコンストラクタでは生成インスタンスid_が無効値なのでswapで事足りる
		// ムーブ代入はこの限りではないのでjoinable()判定が必要
		swap(source.instance);
	}

	~thread(void)
	{
		if (joinable())
		{
			std::terminate();
		}
	}

	thread& operator=(STD11_RV_REF(thread) source)
	{
		if (joinable())
		{
			std::terminate();
		}

		swap(source.instance);
		return *this;
	}

	void swap(thread& x) throw ()
	{
		std::swap(id_, x.id_);
		std::swap(procedure_, x.procedure_);
	}

	bool joinable() const throw ()
	{
		return !(id_ == id());
	}

	void join()
	{
		if (joinable())
		{
			pthread_join(id_.native_thread_id_, NULL);
			id_ = id();
		}
		else
		{
			// throw std11::system_error(invalid_argument);
		}
	}

	void detach()
	{
		if (joinable())
		{
			pthread_detach(id_.native_thread_id_);
			id_ = id();
		}
		else
		{
			// throw std11::system_error(invalid_argument);
		}
	}

	id get_id(void) const throw ()
	{
		return id_;
	}

	static unsigned int hardware_concurrency() throw ()
	{
		return static_cast<unsigned int>(sysconf(_SC_NPROCESSORS_ONLN));
	}
};

template<>
struct hash<thread::id>
{
	size_t operator()(const thread::id& id) const
	{
		return static_cast<size_t>(id.native_thread_id_);
	}
};

namespace this_thread
{

inline thread::id get_id()
{
	return thread::id(pthread_self());
}

inline void yield(void)
{
	sched_yield();
}

//template<class Clock, class Duration>
//void sleep_until(const chrono::time_point<Clock, Duration>& abs_time)
//{
//
//}
//
//template<class Rep, class Period>
//void sleep_for(const chrono::duration<Rep, Period>& rel_time)
//{
//
//}

}// namespace this_thread

}  // namespace std11

#endif /* STDBP_STD11_THREAD_H_ */
