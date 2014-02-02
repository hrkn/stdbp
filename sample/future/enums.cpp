#include <iostream>
#include "std11/type_traits.hpp"
#include "std11/future.hpp"

#define PRINT(x)  std::cout << #x " = " << x << std::endl
#define PRINT_CMP(x, y)  std::cout << "(" #x " == " #y ") -> " << (x == y) << std::endl

int main()
{
	using namespace std11;

	std::cout << std::boolalpha;
	PRINT(future_status::ready);
	PRINT((is_same<future_status, future_status>::value));
	PRINT((is_same<future_status, future_errc>::value));
	PRINT_CMP(future_status::ready, future_status::ready);
	PRINT_CMP(future_status::ready, future_status::deffered);
	PRINT_CMP(future_status::ready, future_errc::broken_promise);
	PRINT_CMP(future_errc::broken_promise, future_errc::broken_promise);
	PRINT(is_error_code_enum<future_errc>::value);

	return 0;
}

