#include <string>
#include <iostream>
#include "std11/numeric.hpp"
#include "std11/algorithm.hpp"

int main()
{
	std::string s = "hello, iota!";
	std::cout << s << std::endl;
	std11::iota(s.begin(), s.end(), 'A');
	std::cout << s << std::endl;
//	std11::random_shuffle(s.begin(), s.end());
//	std::cout << s << std::endl;

	return 0;
}

