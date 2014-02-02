/*
 * type_traits.hpp
 *
 */

#ifndef STDBP_STD11_TYPE_TRAITS_HPP_
#define STDBP_STD11_TYPE_TRAITS_HPP_

#include <cstddef>

#include "std11/_config.hpp"
#include "std11/utility.hpp"

namespace std11
{

template<typename T, T v>
struct integral_constant
{
	static T const value = v;
	typedef T value_type;
	typedef integral_constant<T, v> type;
	operator value_type() const
	{
		return value;
	}
};

typedef integral_constant<bool, true> true_type;

typedef integral_constant<bool, false> false_type;

template<typename T, T v>
T const integral_constant<T, v>::value;

namespace detail
{

struct sfinae_types
{
	typedef char one;
	typedef struct
	{
		char arr[2];
	} two;
};

template<typename Type>
struct in_array: public sfinae_types
{
private:
	template<typename Up>
	static one test(Up (*)[1]);

	template<typename >
	static two test(...);

public:
	static const bool value = sizeof(test<Type>(0)) == 1;
};

template<typename Type>
struct is_union_or_class_helper: public sfinae_types
{
private:
	template<typename Up>
	static one test(int Up::*);

	template<typename >
	static two test(...);

public:
	static const bool value = sizeof(test<Type>(0)) == 1;
};

template<typename Type>
struct is_union_or_class: public integral_constant<bool,
		is_union_or_class_helper<Type>::value>
{
};
}  // namespace detail

#define GENERATE_DEFAULT(PRED) \
	template<typename> \
	struct PRED: public false_type {}

#define GENERATE_TRUE(PRED, TYPE) \
	template<> \
	struct PRED<TYPE>: public true_type {}

#define GENERATE_FALSE(PRED, TYPE) \
	template<> \
	struct PRED<TYPE>: public false_type {}

// Partially specialized helpers
#define GENERATE_PS_TRUE(PRED, PS_TYPE, TYPE) \
	template<typename PS_TYPE> \
	struct PRED<TYPE>: public true_type {}

#define GENERATE_PS_FALSE(PRED, TYPE) \
	template<typename PS_TYPE> \
	struct PRED<TYPE>: public false_type {}

namespace traits_helper
{

GENERATE_DEFAULT(is_void);
GENERATE_TRUE(is_void, void);

GENERATE_DEFAULT(is_integral);
GENERATE_TRUE(is_integral, bool);
GENERATE_TRUE(is_integral, char);
GENERATE_TRUE(is_integral, signed char);
GENERATE_TRUE(is_integral, unsigned char);
GENERATE_TRUE(is_integral, wchar_t);
GENERATE_TRUE(is_integral, short);
GENERATE_TRUE(is_integral, unsigned short);
GENERATE_TRUE(is_integral, int);
GENERATE_TRUE(is_integral, unsigned int);
GENERATE_TRUE(is_integral, long);
GENERATE_TRUE(is_integral, unsigned long);
GENERATE_TRUE(is_integral, long long);
GENERATE_TRUE(is_integral, unsigned long long);

GENERATE_DEFAULT(is_floating_point);
GENERATE_TRUE(is_floating_point, float);
GENERATE_TRUE(is_floating_point, double);
GENERATE_TRUE(is_floating_point, long double);

GENERATE_DEFAULT(is_array);
template<typename T, std::size_t SIZE>
struct is_array<T[SIZE]> : public true_type
{
};
template<typename T>
struct is_array<T[]> : public true_type
{
};

GENERATE_DEFAULT(is_pointer);
GENERATE_PS_TRUE(is_pointer, T, T*);

GENERATE_DEFAULT(is_reference);
GENERATE_PS_TRUE(is_reference, T, T&);
GENERATE_PS_TRUE(is_reference, T, STD11_RV_REF(T));

GENERATE_DEFAULT(is_member_pointer);
template<typename T, typename ClassName>
struct is_member_pointer<T ClassName::*>: public true_type
{
};

}  // namespace helpers

#define FORWARD_DECLARATION(PRED, ...) template<__VA_ARGS__> struct PRED

FORWARD_DECLARATION(remove_cv, typename);
#define GENERATE_FROM_HELPER(PRED) \
	template<typename T> \
	struct PRED : public integral_constant<bool, \
		(traits_helper::PRED<typename remove_cv<T>::type>::value)> {}

// is_void
GENERATE_FROM_HELPER(is_void);

// is_integral
GENERATE_FROM_HELPER(is_integral);

// is_floating_point
GENERATE_FROM_HELPER(is_floating_point);

// is_array
GENERATE_FROM_HELPER(is_array);

// is_pointer
GENERATE_FROM_HELPER(is_pointer);

// is_lvalue_reference -> INDETERMINABLE

// is_rvalue_reference -> INDETERMINABLE

// is_member_object_pointer

// is_member_function_pointer

// is_enum : enum型
FORWARD_DECLARATION(is_member_pointer, typename);
FORWARD_DECLARATION(is_fundamental, typename);
FORWARD_DECLARATION(is_reference, typename);
template<typename Type>
struct is_enum: public integral_constant<bool,
!(is_fundamental<Type>::value || is_array<Type>::value
		|| is_pointer<Type>::value || is_reference<Type>::value
		|| is_member_pointer<Type>::value
		|| detail::is_union_or_class<Type>::value)>
{
};

// is_union -> INDETERMINABLE

// is_class -> INDETERMINABLE

// is_function : 関数型
FORWARD_DECLARATION(is_reference, typename);
template<typename Type>
struct is_function: public integral_constant<bool,
!(detail::in_array<Type>::value
		|| detail::is_union_or_class<Type>::value
		|| is_reference<Type>::value || is_void<Type>::value)>
{
};

// is_reference
GENERATE_FROM_HELPER(is_reference);

// is_arithmetic : 算術型(整数型/浮動小数点型)
template<typename Type>
struct is_arithmetic: public integral_constant<bool,
(is_integral<Type>::value || is_floating_point<Type>::value)>
{
};

// is_fundamental : 基本型(整数型/浮動小数点型/void型)
template<typename Type>
struct is_fundamental: public integral_constant<bool,
		(is_arithmetic<Type>::value || is_void<Type>::value)>
{
};

// is_object : オブジェクト型( not(関数型/参照型/void型) )
template<typename Type>
struct is_object: public integral_constant<bool,
		!(is_function<Type>::value || is_reference<Type>::value
				|| is_void<Type>::value)>
{
};

// is_scalar : スカラ型(整数型/浮動小数点数型/ポインタ型/メンバポインタ型)
template<typename Type>
struct is_scalar: public integral_constant<bool,
		(is_arithmetic<Type>::value || is_member_pointer<Type>::value
				|| is_pointer<Type>::value || is_enum<Type>::value)>
{
};

// is_compound : 複合型( not(基本型...整数型/浮動小数点数型/void型) )
template<typename Type>
struct is_compound: public integral_constant<bool,
		!(is_fundamental<Type>::value)>
{
};

// is_member_pointer
GENERATE_FROM_HELPER(is_member_pointer);

// is_const
GENERATE_DEFAULT(is_const);
GENERATE_PS_TRUE(is_const, T, T const);

// is_volatile
GENERATE_DEFAULT(is_volatile);
GENERATE_PS_TRUE(is_volatile, T, T volatile);

// is_trivial
// is_trivially_copyable
// is_standard_layout
// is_pod
// is_literal_type
// is_empty
// is_polymorphic
// is_abstract
// is_signed
// is_unsigned
// is_constructible
// is_default_constructible
// is_copy_constructible
// is_move_constructible
// is_assignable
// is_copy_assignable
// is_move_assignable
// is_destructible
// is_trivially_constructible
// is_trivially_default_constructible
// is_trivially_copy_constructible
// is_trivially_move_constructible
// is_trivially_assignable
// is_trivially_copy_assignable
// is_trivially_move_assignable
// is_trivially_destructible
// is_nothrow_constructible
// is_nothrow_default_constructible
// is_nothrow_copy_constructible
// is_nothrow_move_constructible
// is_nothrow_assignable
// is_nothrow_copy_assignable
// is_nothrow_move_assignable
// is_nothrow_destructible
// has_virtual_destructor

// alignment_of

// rank
template <typename T>
struct rank: public integral_constant<std::size_t, 0>
{
};

template <typename T>
struct rank<T[]>: public integral_constant<std::size_t,
	rank<T>::value + 1>
{
};

template <typename T, std::size_t N>
struct rank<T[N]>: public integral_constant<std::size_t,
	rank<T>::value + 1>
{
};

// extent
template<typename, unsigned>
struct extent: public integral_constant<std::size_t, 0>
{
};

template<typename T, unsigned I, std::size_t N>
struct extent<T[N], I>: public integral_constant<std::size_t,
	I == 0 ? N : extent<T, I - 1>::value>
{
};

template<typename T, unsigned I>
struct extent<T[], I>: public integral_constant<std::size_t,
	I == 0 ? 0 : extent<T, I - 1>::value>
{
};

// is_same
template<typename, typename>
struct is_same
{
	static bool const value = false;
};

template<typename Type>
struct is_same<Type, Type>
{
	static bool const value = true;
};

// is_base_of
// is_convertible

// remove_const
template<typename T>
struct remove_const
{
	typedef T type;
};

template<typename T>
struct remove_const<T const>
{
	typedef T type;
};

// remove_volatile
template<typename T>
struct remove_volatile
{
	typedef T type;
};

template<typename T>
struct remove_volatile<T volatile>
{
	typedef T type;
};

// remove_cv
template<typename T>
struct remove_cv
{
	typedef typename remove_const<typename remove_volatile<T>::type>::type type;
};

// add_const
template<typename T>
struct add_const
{
	typedef T const type;
};

// add_volatile
template<typename T>
struct add_volatile
{
	typedef T volatile type;
};

// add_cv
template <typename T>
struct add_cv
{
	typedef typename add_const<typename add_volatile<T>::type>::type type;
};

// remove_reference
template<typename Type>
struct remove_reference
{
	typedef Type type;
};

template<typename Type>
struct remove_reference<Type&>
{
	typedef Type type;
};

// add_lvalue_reference
FORWARD_DECLARATION(conditional, bool, typename, typename);
template<typename T>
struct add_lvalue_reference
{
	typedef typename conditional<
		is_object<T>::value || is_function<T>::value,
		T&,
		T
	>::type type;
};

// add_rvalue_reference
template<typename T>
struct add_rvalue_reference
{
	typedef STD11_RV_REF(T) type;
};

template<typename T>
struct add_rvalue_reference<STD11_RV_REF(T)>
{
	typedef STD11_RV_REF(T) type;
};

// make_signed
template<typename T>
struct make_signed
{
//	static_assert(!is_same<T, bool>::value, "T mustn't bool");
	typedef T type;
};

template<>
struct make_signed<char>
{
	typedef signed char type;
};

template<>
struct make_signed<unsigned char>
{
	typedef signed char type;
};

template<>
struct make_signed<unsigned short>
{
	typedef signed short type;
};

template<>
struct make_signed<unsigned int>
{
	typedef signed int type;
};

template<>
struct make_signed<unsigned long>
{
	typedef signed long type;
};

template<>
struct make_signed<unsigned long long>
{
	typedef signed long long type;
};

// make_unsigned
template<typename T>
struct make_unsigned
{
//	static_assert(!is_same<T, bool>::value, "T mustn't bool");
	typedef T type;
};

template<>
struct make_unsigned<char>
{
	typedef unsigned char type;
};

template<>
struct make_unsigned<signed char>
{
	typedef unsigned char type;
};

template<>
struct make_unsigned<short>
{
	typedef unsigned short type;
};

template<>
struct make_unsigned<int>
{
	typedef unsigned int type;
};

template<>
struct make_unsigned<long>
{
	typedef unsigned long type;
};

template<>
struct make_unsigned<long long>
{
	typedef unsigned long long type;
};

// remove_extent
template<typename T>
struct remove_extent
{
	typedef T type;
};
template<typename T>
struct remove_extent<T[]>
{
	typedef T type;
};
template<typename T, std::size_t N>
struct remove_extent<T[N]>
{
	typedef T type;
};

// remove_all_extents
template<typename T>
struct remove_all_extents
{
	typedef T type;
};
template<typename T>
struct remove_all_extents<T[]>
{
	typedef typename remove_all_extents<T>::type type;
};
template<typename T, std::size_t N>
struct remove_all_extents<T[N]>
{
	typedef typename remove_all_extents<T>::type type;
};

// add_pointer
template<typename T>
struct add_pointer
{
	typedef typename remove_reference<T>::type* type;
};

// remove_pointer
template<typename T>
struct remove_pointer
{
	typedef typename remove_reference<T>::type type;
};

template<typename T>
struct remove_pointer<T*>
{
	typedef typename remove_reference<T>::type type;
};

// aligned_storage
// aligned_union
// decay
template<bool Cond, typename Then, typename Else>
struct conditional;

template<typename T>
struct decay
{
	typedef typename remove_reference<T>::type U;
	typedef typename conditional<
		is_array<U>::value,
		typename remove_extent<U>::type*,
		typename conditional<
			is_function<U>::value,
			typename add_pointer<U>::type,
			typename remove_cv<U>::type
		>::type
	>::type type;
};

// enable_if
template<bool Cond, typename T = void>
struct enable_if
{
};
template<typename T>
struct enable_if<true, T>
{
	typedef T type;
};

// conditional
template<bool Cond, class Then, class Else>
struct conditional;

template<class Then, class Else>
struct conditional<true, Then, Else>
{
	typedef Then type;
};

template<class Then, class Else>
struct conditional<false, Then, Else>
{
	typedef Else type;
};

// common_type
// underlying_type
// result_of

#undef FORWARD_DECLARATION
#undef GENERATE_FROM_HELPER
#undef GENERATE_DEFAULT
#undef GENERATE_TRUE
#undef GENERATE_FALSE
#undef GENERATE_PS_TRUE
#undef GENERATE_PS_FALSE

}  // namespace std11

#endif /* STDBP_STD11_TYPE_TRAITS_HPP_ */
