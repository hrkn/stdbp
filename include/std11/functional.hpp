/*
 * functional.hpp
 *
 */

#ifndef STDBP_STD11_FUNCTIONAL_HPP_
#define STDBP_STD11_FUNCTIONAL_HPP_

#include <cstddef>

#include <functional>
#include <exception>

#include "std11/_config.hpp"
#include "std11/utility.hpp"
#include "std11/type_traits.hpp"
#include "std11/memory.hpp"
#include "std11/internal/functional/bind.hpp"
#include "std11/internal/functional/mem_fn.hpp"

#define STDBP_STD11_TEMPLATE_PARAMS_1  class T0
#define STDBP_STD11_TEMPLATE_PARAMS_2  class T0, class T1
#define STDBP_STD11_TEMPLATE_PARAMS_3  class T0, class T1, class T2
#define STDBP_STD11_TEMPLATE_PARAMS_4  class T0, class T1, class T2, class T3
#define STDBP_STD11_TEMPLATE_PARAMS_5  class T0, class T1, class T2, class T3, class T4
#define STDBP_STD11_TEMPLATE_PARAMS_6  class T0, class T1, class T2, class T3, class T4, class T5
#define STDBP_STD11_TEMPLATE_PARAMS_7  class T0, class T1, class T2, class T3, class T4, class T5, class T6
#define STDBP_STD11_TEMPLATE_PARAMS_8  class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7
#define STDBP_STD11_TEMPLATE_PARAMS_9  class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8
#define STDBP_STD11_TEMPLATE_PARAMS_10 class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9

#define STDBP_STD11_TEMPLATE_ARGS_1   T0
#define STDBP_STD11_TEMPLATE_ARGS_2   T0, T1
#define STDBP_STD11_TEMPLATE_ARGS_3   T0, T1, T2
#define STDBP_STD11_TEMPLATE_ARGS_4   T0, T1, T2, T3
#define STDBP_STD11_TEMPLATE_ARGS_5   T0, T1, T2, T3, T4
#define STDBP_STD11_TEMPLATE_ARGS_6   T0, T1, T2, T3, T4, T5
#define STDBP_STD11_TEMPLATE_ARGS_7   T0, T1, T2, T3, T4, T5, T6
#define STDBP_STD11_TEMPLATE_ARGS_8   T0, T1, T2, T3, T4, T5, T6, T7
#define STDBP_STD11_TEMPLATE_ARGS_9   T0, T1, T2, T3, T4, T5, T6, T7, T8
#define STDBP_STD11_TEMPLATE_ARGS_10  T0, T1, T2, T3, T4, T5, T6, T7, T8, T9

#define STDBP_STD11_FUNCTION_PARAMS_1  T0 t0
#define STDBP_STD11_FUNCTION_PARAMS_2  T0 t0, T1 t1
#define STDBP_STD11_FUNCTION_PARAMS_3  T0 t0, T1 t1, T2 t2
#define STDBP_STD11_FUNCTION_PARAMS_4  T0 t0, T1 t1, T2 t2, T3 t3
#define STDBP_STD11_FUNCTION_PARAMS_5  T0 t0, T1 t1, T2 t2, T3 t3, T4 t4
#define STDBP_STD11_FUNCTION_PARAMS_6  T0 t0, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5
#define STDBP_STD11_FUNCTION_PARAMS_7  T0 t0, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6
#define STDBP_STD11_FUNCTION_PARAMS_8  T0 t0, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7
#define STDBP_STD11_FUNCTION_PARAMS_9  T0 t0, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8
#define STDBP_STD11_FUNCTION_PARAMS_10 T0 t0, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9

#define STDBP_STD11_FUNCTION_ARGS_1   t0
#define STDBP_STD11_FUNCTION_ARGS_2   t0, t1
#define STDBP_STD11_FUNCTION_ARGS_3   t0, t1, t2
#define STDBP_STD11_FUNCTION_ARGS_4   t0, t1, t2, t3
#define STDBP_STD11_FUNCTION_ARGS_5   t0, t1, t2, t3, t4
#define STDBP_STD11_FUNCTION_ARGS_6   t0, t1, t2, t3, t4, t5
#define STDBP_STD11_FUNCTION_ARGS_7   t0, t1, t2, t3, t4, t5, t6
#define STDBP_STD11_FUNCTION_ARGS_8   t0, t1, t2, t3, t4, t5, t6, t7
#define STDBP_STD11_FUNCTION_ARGS_9   t0, t1, t2, t3, t4, t5, t6, t7, t8
#define STDBP_STD11_FUNCTION_ARGS_10  t0, t1, t2, t3, t4, t5, t6, t7, t8, t9

#define STDBP_STD11_FUNCTION_MANAGER_N(Count) \
template <class FunctionPtr, class R, STDBP_STD11_TEMPLATE_PARAMS_##Count>                  \
struct function_ptr_manager##Count {                                                        \
	static R invoke(any_pointer function_ptr, STDBP_STD11_FUNCTION_PARAMS_##Count)          \
	{                                                                                       \
		FunctionPtr func = reinterpret_cast<FunctionPtr>(function_ptr.func_ptr);            \
		return func(STDBP_STD11_FUNCTION_ARGS_##Count);                                     \
	}                                                                                       \
                                                                                            \
	static void destroy(any_pointer)                                                        \
	{                                                                                       \
	}                                                                                       \
                                                                                            \
	static void* clone(any_pointer function_ptr)                                            \
	{                                                                                       \
		return function_ptr.obj_ptr;                                                        \
	}                                                                                       \
                                                                                            \
};                                                                                          \
                                                                                            \
template <class FunctionObj, class R, STDBP_STD11_TEMPLATE_PARAMS_##Count>                  \
struct function_obj_manager##Count {                                                        \
	static R invoke(any_pointer function_obj_ptr, STDBP_STD11_FUNCTION_PARAMS_##Count)      \
	{                                                                                       \
		FunctionObj* func = reinterpret_cast<FunctionObj*>(function_obj_ptr.obj_ptr);       \
		return (*func)(STDBP_STD11_FUNCTION_ARGS_##Count);                                  \
	}                                                                                       \
                                                                                            \
	static void destroy(any_pointer function_obj_ptr)                                       \
	{                                                                                       \
		delete reinterpret_cast<FunctionObj*>(function_obj_ptr.obj_ptr);                    \
	}                                                                                       \
                                                                                            \
	static void* clone(any_pointer function_ptr)                                            \
	{                                                                                       \
		return new FunctionObj(*static_cast<FunctionObj*>(function_ptr.obj_ptr));           \
	}                                                                                       \
};

#define STDBP_STD11_FUNCTION_CLASS_N(Count)   \
template <class R, STDBP_STD11_TEMPLATE_PARAMS_##Count>                                     \
class function<R (STDBP_STD11_TEMPLATE_ARGS_##Count)>                                       \
	: public functional_detail::function_base<R (STDBP_STD11_TEMPLATE_ARGS_##Count)> {      \
public:                                                                                     \
	typedef R result_type;                                                                  \
	typedef functional_detail::any_pointer        any_pointer;                              \
	typedef functional_detail::function_ptr_tag   function_ptr_tag;                         \
	typedef functional_detail::function_obj_tag   function_obj_tag;                         \
	typedef functional_detail::member_ptr_tag     member_ptr_tag;                           \
                                                                                            \
	using functional_detail::function_base<R (STDBP_STD11_TEMPLATE_ARGS_##Count)>::destroy_; \
	using functional_detail::function_base<R (STDBP_STD11_TEMPLATE_ARGS_##Count)>::functor_; \
                                                                                            \
	result_type (*invoke_)(any_pointer, STDBP_STD11_TEMPLATE_ARGS_##Count);                 \
	void* (*clone_)(any_pointer);                                                           \
                                                                                            \
	function()                                                                              \
		: functional_detail::function_base<R (STDBP_STD11_TEMPLATE_ARGS_##Count)>(),        \
		  invoke_(NULL), clone_(NULL)                                                       \
	{                                                                                       \
	}                                                                                       \
                                                                                            \
	function(const function& func)                                                          \
		: functional_detail::function_base<R (STDBP_STD11_TEMPLATE_ARGS_##Count)>(),        \
		  invoke_(NULL), clone_(NULL)                                                       \
	{                                                                                       \
		assign_to_own(func);                                                                \
	}                                                                                       \
                                                                                            \
	template <class FuncType>                                                               \
	function(FuncType func)                                                                 \
		: functional_detail::function_base<R (STDBP_STD11_TEMPLATE_ARGS_##Count)>(),        \
		  invoke_(NULL), clone_(NULL)                                                       \
	{                                                                                       \
		assign_to(func);                                                                    \
	}                                                                                       \
                                                                                            \
	function& operator=(const function& func)                                               \
	{                                                                                       \
		if (&func == this)                                                                  \
		{                                                                                   \
			return *this;                                                                   \
		}                                                                                   \
                                                                                            \
		assign_to_own(func);                                                                \
		return *this;                                                                       \
	}                                                                                       \
                                                                                            \
	template <class FuncType>                                                               \
	function& operator=(FuncType func)                                                      \
	{                                                                                       \
		clear();                                                                            \
		assign_to(func);                                                                    \
		return *this;                                                                       \
	}                                                                                       \
                                                                                            \
	result_type operator()(STDBP_STD11_FUNCTION_PARAMS_##Count) const                       \
	{                                                                                       \
		if (invoke_ == NULL)                                                                \
		{                                                                                   \
			throw bad_function_call();                                                      \
		}                                                                                   \
		return invoke_(functor_, STDBP_STD11_FUNCTION_ARGS_##Count);                        \
	}                                                                                       \
                                                                                            \
	void clear()                                                                            \
	{                                                                                       \
		if (!empty())                                                                       \
		{                                                                                   \
			destroy_(functor_);                                                             \
                                                                                            \
			destroy_ = NULL;                                                                \
			invoke_ = NULL;                                                                 \
			clone_ = NULL;                                                                  \
		}                                                                                   \
	}                                                                                       \
                                                                                            \
	bool empty() const                                                                      \
	{                                                                                       \
		return !(invoke_ && destroy_);                                                      \
	}                                                                                       \
                                                                                            \
	operator bool()                                                                         \
	{                                                                                       \
		return !empty();                                                                    \
	}                                                                                       \
                                                                                            \
	bool operator!()                                                                        \
	{                                                                                       \
		return empty();                                                                     \
	}                                                                                       \
                                                                                            \
private:                                                                                    \
	template <class FuncType>                                                               \
	void assign_to(FuncType func)                                                           \
	{                                                                                       \
		typedef typename functional_detail::get_function_tag<FuncType>::type tag;           \
		assign_to(func, tag());                                                             \
	}                                                                                       \
                                                                                            \
	template <class FunctionPtr>                                                            \
	void assign_to(FunctionPtr func, function_ptr_tag)                                      \
	{                                                                                       \
		typedef                                                                             \
			functional_detail::function_ptr_manager##Count<FunctionPtr, R, STDBP_STD11_TEMPLATE_ARGS_##Count> \
		actual_manager;                                                                     \
                                                                                            \
		destroy_ = &actual_manager::destroy;                                                \
		invoke_ = &actual_manager::invoke;                                                  \
		clone_ = &actual_manager::clone;                                                    \
                                                                                            \
		functor_.func_ptr = reinterpret_cast<void (*)()>(func);                             \
	}                                                                                       \
                                                                                            \
	template <class FunctionObj>                                                            \
	void assign_to(FunctionObj func, function_obj_tag)                                      \
	{                                                                                       \
		typedef                                                                             \
			functional_detail::function_obj_manager##Count<FunctionObj, R, STDBP_STD11_TEMPLATE_ARGS_##Count> \
		actual_manager;                                                                     \
                                                                                            \
		destroy_ = &actual_manager::destroy;                                                \
		invoke_ = &actual_manager::invoke;                                                  \
		clone_ = &actual_manager::clone;                                                    \
                                                                                            \
		FunctionObj* new_func = new FunctionObj(func);                                      \
		functor_.obj_ptr = static_cast<void*>(new_func);                                    \
	}                                                                                       \
                                                                                            \
	template <class MemberPtr>                                                              \
	void assign_to(MemberPtr func, member_ptr_tag)                                          \
	{                                                                                       \
		assign_to(mem_fn(func));                                                            \
	}                                                                                       \
                                                                                            \
	void assign_to_own(const function& func)                                                \
	{                                                                                       \
		clear();                                                                            \
		destroy_ = func.destroy_;                                                           \
		invoke_ = func.invoke_;                                                             \
		clone_ = func.clone_;                                                               \
		if (func.clone_ != NULL)                                                            \
		{                                                                                   \
			functor_.obj_ptr = func.clone_(func.functor_);                                  \
		}                                                                                   \
	}                                                                                       \
};

namespace std11
{

namespace functional_detail
{

union any_pointer
{
	void* obj_ptr;
	void (*func_ptr)(); // 関数ポインタとvoid*間のキャストは許されない為必要
};

// == 関数判別タグ ==
// 関数ポインタ
struct function_ptr_tag
{
};
// 関数オブジェクト
struct function_obj_tag
{
};
// メンバ関数ポインタ
struct member_ptr_tag
{
};

template<class FuncType>
struct get_function_tag
{
private:
	typedef typename conditional<std11::is_pointer<FuncType>::value,
			function_ptr_tag, FuncType>::type func_ptr_tag;

	typedef typename conditional<std11::is_member_pointer<func_ptr_tag>::value,
			member_ptr_tag, func_ptr_tag>::type function_or_member_ptr_tag;

	typedef typename conditional<
			std11::is_same<FuncType, function_or_member_ptr_tag>::value,
			function_obj_tag, function_or_member_ptr_tag>::type ret_type;

public:
	typedef ret_type type;
};

template<class FunctionPtr, class R>
struct function_ptr_manager0
{
	static R invoke(any_pointer function_ptr)
	{
		FunctionPtr func = reinterpret_cast<FunctionPtr>(function_ptr.func_ptr);
		return func();
	}

	static void destroy(any_pointer)
	{
	}

	static void* clone(any_pointer function_ptr)
	{
		return function_ptr.obj_ptr;
	}
};

template<class FunctionObj, class R>
struct function_obj_manager0
{
	static R invoke(any_pointer function_obj_ptr)
	{
		FunctionObj* func =
				reinterpret_cast<FunctionObj*>(function_obj_ptr.obj_ptr);
		return (*func)();
	}

	static void destroy(any_pointer function_obj_ptr)
	{
		delete reinterpret_cast<FunctionObj*>(function_obj_ptr.obj_ptr);;
	}

	static void* clone(any_pointer function_ptr)
	{
		return new FunctionObj(*static_cast<FunctionObj*>(function_ptr.obj_ptr));
	}
};

STDBP_STD11_FUNCTION_MANAGER_N(1);
STDBP_STD11_FUNCTION_MANAGER_N(2);
STDBP_STD11_FUNCTION_MANAGER_N(3);
STDBP_STD11_FUNCTION_MANAGER_N(4);
STDBP_STD11_FUNCTION_MANAGER_N(5);
STDBP_STD11_FUNCTION_MANAGER_N(6);
STDBP_STD11_FUNCTION_MANAGER_N(7);
STDBP_STD11_FUNCTION_MANAGER_N(8);
STDBP_STD11_FUNCTION_MANAGER_N(9);
STDBP_STD11_FUNCTION_MANAGER_N(10);

template<class Signature>
class function_base
{
protected:
	typedef functional_detail::any_pointer any_pointer;

public:
	void (*destroy_)(any_pointer);
	any_pointer functor_;

	function_base() :
			destroy_(NULL), functor_()
	{
	}

	virtual ~function_base()
	{
		if (destroy_ != NULL)
		{
			destroy_(functor_);
			destroy_ = NULL;
		}
	}
};

}  // namespace functional_detail

class bad_function_call: public std::exception
{
	virtual char const* what() const throw ()
	{
		return "empty function call";
	}
};

template<class Signature>
class function;

template<class R>
class function<R(void)> : public functional_detail::function_base<R(void)>
{
public:
	typedef R result_type;
	typedef functional_detail::any_pointer any_pointer;
	typedef functional_detail::function_ptr_tag function_ptr_tag;
	typedef functional_detail::function_obj_tag function_obj_tag;
	typedef functional_detail::member_ptr_tag member_ptr_tag;

	using functional_detail::function_base<R(void)>::destroy_;
	using functional_detail::function_base<R(void)>::functor_;

	result_type (*invoke_)(any_pointer);
	void* (*clone_)(any_pointer);

	function() :
			functional_detail::function_base<R(void)>(), invoke_(NULL), clone_(
					NULL)
	{
	}

	function(const function& func) :
			functional_detail::function_base<R(void)>(), invoke_(NULL), clone_(
					NULL)
	{
		assign_to_own(func);
	}

	template<class FuncType>
	function(FuncType func) :
			functional_detail::function_base<R(void)>(), invoke_(NULL), clone_(
					NULL)
	{
		assign_to(func);
	}

	function& operator=(const function& func)
	{
		if (&func == this)
		{
			return *this;
		}

		assign_to_own(func);
		return *this;
	}

	template<class FuncType>
	function& operator=(FuncType func)
	{
		clear();
		assign_to(func);

		return *this;
	}

	result_type operator()() const
	{
		if (invoke_ == NULL)
		{
			throw bad_function_call();
		}
		return invoke_(functor_);
	}

	void clear()
	{
		if (!empty())
		{
			destroy_(functor_);

			destroy_ = NULL;
			invoke_ = NULL;
			clone_ = NULL;
		}
	}

	bool empty() const
	{
		return !(invoke_ && destroy_);
	}

	operator bool()
	{
		return !empty();
	}

	bool operator!()
	{
		return empty();
	}

private:
	template<class FuncType>
	void assign_to(FuncType func)
	{
		typedef typename functional_detail::get_function_tag<FuncType>::type tag;
		assign_to(func, tag());
	}

	template<class FunctionPtr>
	void assign_to(FunctionPtr func, function_ptr_tag)
	{
		typedef functional_detail::function_ptr_manager0<FunctionPtr, R> actual_manager;

		destroy_ = &actual_manager::destroy;
		invoke_ = &actual_manager::invoke;
		clone_ = &actual_manager::clone;

		functor_.func_ptr = reinterpret_cast<void (*)()>(func);}

		template <class FunctionObj>
		void assign_to(FunctionObj func, function_obj_tag)
		{
			typedef functional_detail::function_obj_manager0<FunctionObj, R>actual_manager;

		destroy_ = &actual_manager::destroy;
		invoke_ = &actual_manager::invoke;
		clone_ = &actual_manager::clone;

		FunctionObj* new_func = new FunctionObj(func);
		functor_.obj_ptr = static_cast<void*>(new_func);
	}

	void assign_to_own(const function& func)
	{
		clear();
		destroy_    = func.destroy_;
		invoke_     = func.invoke_;
		clone_      = func.clone_;
		if (func.clone_ != NULL)
		{
			functor_.obj_ptr = func.clone_(func.functor_);
		}
	}
};

STDBP_STD11_FUNCTION_CLASS_N(1)
STDBP_STD11_FUNCTION_CLASS_N(2)
STDBP_STD11_FUNCTION_CLASS_N(3)
STDBP_STD11_FUNCTION_CLASS_N(4)
STDBP_STD11_FUNCTION_CLASS_N(5)
STDBP_STD11_FUNCTION_CLASS_N(6)
STDBP_STD11_FUNCTION_CLASS_N(7)
STDBP_STD11_FUNCTION_CLASS_N(8)
STDBP_STD11_FUNCTION_CLASS_N(9)
STDBP_STD11_FUNCTION_CLASS_N(10)

#undef STDBP_STD11_TEMPLATE_PARAMS_1
#undef STDBP_STD11_TEMPLATE_PARAMS_2
#undef STDBP_STD11_TEMPLATE_PARAMS_3
#undef STDBP_STD11_TEMPLATE_PARAMS_4
#undef STDBP_STD11_TEMPLATE_PARAMS_5
#undef STDBP_STD11_TEMPLATE_PARAMS_6
#undef STDBP_STD11_TEMPLATE_PARAMS_7
#undef STDBP_STD11_TEMPLATE_PARAMS_8
#undef STDBP_STD11_TEMPLATE_PARAMS_9
#undef STDBP_STD11_TEMPLATE_PARAMS_10

#undef STDBP_STD11_TEMPLATE_ARGS_1
#undef STDBP_STD11_TEMPLATE_ARGS_2
#undef STDBP_STD11_TEMPLATE_ARGS_3
#undef STDBP_STD11_TEMPLATE_ARGS_4
#undef STDBP_STD11_TEMPLATE_ARGS_5
#undef STDBP_STD11_TEMPLATE_ARGS_6
#undef STDBP_STD11_TEMPLATE_ARGS_7
#undef STDBP_STD11_TEMPLATE_ARGS_8
#undef STDBP_STD11_TEMPLATE_ARGS_9
#undef STDBP_STD11_TEMPLATE_ARGS_10

#undef STDBP_STD11_FUNCTION_PARAMS_1
#undef STDBP_STD11_FUNCTION_PARAMS_2
#undef STDBP_STD11_FUNCTION_PARAMS_3
#undef STDBP_STD11_FUNCTION_PARAMS_4
#undef STDBP_STD11_FUNCTION_PARAMS_5
#undef STDBP_STD11_FUNCTION_PARAMS_6
#undef STDBP_STD11_FUNCTION_PARAMS_7
#undef STDBP_STD11_FUNCTION_PARAMS_8
#undef STDBP_STD11_FUNCTION_PARAMS_9
#undef STDBP_STD11_FUNCTION_PARAMS_10

#undef STDBP_STD11_FUNCTION_ARGS_1
#undef STDBP_STD11_FUNCTION_ARGS_2
#undef STDBP_STD11_FUNCTION_ARGS_3
#undef STDBP_STD11_FUNCTION_ARGS_4
#undef STDBP_STD11_FUNCTION_ARGS_5
#undef STDBP_STD11_FUNCTION_ARGS_6
#undef STDBP_STD11_FUNCTION_ARGS_7
#undef STDBP_STD11_FUNCTION_ARGS_8
#undef STDBP_STD11_FUNCTION_ARGS_9
#undef STDBP_STD11_FUNCTION_ARGS_10

#undef STDBP_STD11_FUNCTION_MANAGER_N
#undef STDBP_STD11_FUNCTION_CLASS_N

template<typename T>
class reference_wrapper
{
	typename remove_reference<T>::type* ptr_;

public:
	reference_wrapper(T& ref) throw () :
			ptr_(addressof(ref))
	{
	}

	reference_wrapper(reference_wrapper<T> const& ref_rapper) throw () :
			ptr_(addressof(ref_rapper.get()))
	{
	}

	reference_wrapper& operator=(reference_wrapper<T> const& x) throw ()
	{
		ptr_ = addressof(x.get());
	}

	T& get(void) const throw ()
	{
		return *ptr_;
	}

	operator T&(void) const throw ()
	{
		return *ptr_;
	}

	// TODO consider whether implementable ...
//	result_of<T(...)>::type operator ()(...) const
//	{
//		return (*ptr)(...);
//	}
}
;

template<typename T>
reference_wrapper<T> ref(T& t) throw ()
{
	return reference_wrapper<T>(t);
}

template<typename T>
reference_wrapper<T> ref(reference_wrapper<T> wrapper) throw ()
{
	return wrapper;
}

template<typename T>
reference_wrapper<T const> cref(T const& t) throw ()
{
	return reference_wrapper<T const>(t);
}

template<typename T>
reference_wrapper<T const> cref(reference_wrapper<T const> wrapper) throw ()
{
	return wrapper;
}

namespace hash_detail
{

inline std::size_t hash_bytes(void const* data, std::size_t length, std::size_t seed =
		static_cast<std::size_t>(0xc1f0f1cdUL)) throw ()
{
	unsigned char const* p = static_cast<unsigned char const*>(data);
	std::size_t hashval = seed;

	for (std::size_t i = 0; i < length; ++i)
	{
		hashval ^= static_cast<std::size_t>(p[i] << (i % sizeof(std::size_t) * 8));
	}

	return hashval;
}

template<typename T>
std::size_t hash_bytes(T const& value) throw ()
{
	return hash_bytes(&value, sizeof(T));
}

}  // namespace detail

template<typename T>
struct hash
{
	typedef std::size_t result_type;
	typedef T argument_type;

	hash(void)
	{
	}
	hash(hash const&)
	{
	}
	hash(STD11_RV_REF(hash))
	{
	}
	~hash(void)
	{
	}

	hash& operator=(STD11_RV_REF(hash))
	{
	}
	hash& operator=(hash const&)
	{
	}
};

/// Partial specializations for pointer types.
template<typename T>
struct hash<T*>
{
	std::size_t operator()(T* p) const throw ()
	{
		return reinterpret_cast<std::size_t>(p);
	}
};

#define STDBP_GENERATE_TRIVIAL_HASHER(T) \
	template<> \
	struct hash<T> \
	{ \
		std::size_t operator()(T val) const throw () \
		{ \
			return static_cast<std::size_t>(val); \
		} \
	}

STDBP_GENERATE_TRIVIAL_HASHER(bool);
STDBP_GENERATE_TRIVIAL_HASHER(char);
STDBP_GENERATE_TRIVIAL_HASHER(signed char);
STDBP_GENERATE_TRIVIAL_HASHER(unsigned char);
STDBP_GENERATE_TRIVIAL_HASHER(wchar_t);
STDBP_GENERATE_TRIVIAL_HASHER(short);
STDBP_GENERATE_TRIVIAL_HASHER(unsigned short);
STDBP_GENERATE_TRIVIAL_HASHER(int);
STDBP_GENERATE_TRIVIAL_HASHER(unsigned int);
STDBP_GENERATE_TRIVIAL_HASHER(long);
STDBP_GENERATE_TRIVIAL_HASHER(long long);
STDBP_GENERATE_TRIVIAL_HASHER(unsigned long);
STDBP_GENERATE_TRIVIAL_HASHER(unsigned long long);

#undef STDBP_GENERATE_TRIVIAL_HASHER

/// Specialization for float
template<>
struct hash<float>
{
	std::size_t operator()(float value) const throw ()
	{
		// 0 and -0 both hash to zero.
		return value != 0.0f ? hash_detail::hash_bytes(value) : 0;
	}
};

/// Specialization for double
template<>
struct hash<double>
{
	std::size_t operator()(double value) const throw ()
	{
		// 0 and -0 both hash to zero
		return value != 0.0 ? hash_detail::hash_bytes(value) : 0;
	}
};

/// Specialization for long double
template<>
struct hash<long double>
{
	std::size_t operator()(long double value) const throw ()
	{
		return value != 0.0 ? hash_detail::hash_bytes(value) : 0;
	}
};

}  // namespace std11

#endif /* STDBP_STD11_FUNCTIONAL_HPP_ */
