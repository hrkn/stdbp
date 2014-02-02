#include <stdio.h>
#include <cxxabi.h>

#include <typeinfo>
#include <iostream>

#include "std11/type_traits.hpp"

typedef char char_array[20];
typedef int (*main_func_type)(void);

void types();
void arrays(void);

int main(void)
{
	types();
	arrays();
}

#define TYPES_SHOW_SIZEOF(TYPE) std::cout << "sizeof(" #TYPE ") = " << sizeof(TYPE) << std::endl
#define TYPES_SHOW_TYPEOF(TYPE) std::cout << "typeof(" #TYPE ") = " << abi::__cxa_demangle(typeid(TYPE).name(), 0, 0, NULL) << std::endl
void types()
{
	char_array c;
	typedef std11::decay<char_array>::type decayed_c;
	TYPES_SHOW_SIZEOF(c);
	TYPES_SHOW_SIZEOF(char_array);
	TYPES_SHOW_SIZEOF(decayed_c);

	typedef std11::decay<main_func_type>::type decayed_main_func;
	TYPES_SHOW_TYPEOF(main);
	TYPES_SHOW_TYPEOF(&main);
	TYPES_SHOW_TYPEOF(decayed_main_func);

	decayed_main_func f = main;
	TYPES_SHOW_TYPEOF(f);
}

#define ARRAYS_SHOW_RANK_OF(TYPE) std::cout << "rank of "#TYPE" : " << std11::rank<TYPE>::value << std::endl
#define ARRAYS_SHOW_EXTENT_OF(TYPE, I) std::cout << "extent("#I") of "#TYPE" : " << std11::extent<TYPE, I>::value << std::endl
void arrays(void)
{
	ARRAYS_SHOW_RANK_OF(int        );
	ARRAYS_SHOW_RANK_OF(int[10]    );
	ARRAYS_SHOW_RANK_OF(int[][10]  );
	ARRAYS_SHOW_RANK_OF(int[][2][1]);
	ARRAYS_SHOW_EXTENT_OF(int        , 0);
	ARRAYS_SHOW_EXTENT_OF(int[10]    , 0);
	ARRAYS_SHOW_EXTENT_OF(int[10]    , 1);
	ARRAYS_SHOW_EXTENT_OF(int[][10]  , 0);
	ARRAYS_SHOW_EXTENT_OF(int[][10]  , 1);
	ARRAYS_SHOW_EXTENT_OF(int[][10]  , 2);
	ARRAYS_SHOW_EXTENT_OF(int[][2][1], 0);
	ARRAYS_SHOW_EXTENT_OF(int[][2][1], 1);
	ARRAYS_SHOW_EXTENT_OF(int[][2][1], 2);
	ARRAYS_SHOW_EXTENT_OF(int[][2][1], 3);
}

