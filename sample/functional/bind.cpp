#include <iostream>
#include <vector>
#include <algorithm>
#include "std11/functional.hpp"

void foo(int n1, int n2, int n3)
{
	std::cout << n1 << "," << n2 << "," << n3 << std::endl;
}

void func(int value)
{
	std::cout << value << std::endl;
}

struct functor
{
	typedef void result_type;
	result_type operator()(int value)
	{
		std::cout << value << std::endl;
	}
};


struct hoge {
	void func(int value)
	{
		std::cout << value << std::endl;
	}
};

bool is_even(int value)
{
	return value % 2 == 0;
}

int add(int lhs, int rhs)
{
	return lhs + rhs;
}

int main()
{
	using namespace std11::placeholders;

	{
		std::vector<int> v;

		v.push_back(3);
		v.push_back(1);
		v.push_back(4);

		std::for_each(v.begin(), v.end(), bind(foo, 0, _1, 9)); // fooの第1引数を0, 第3引数を9に固定
			// 0,3,9
			// 0,1,9
			// 0,4,9

		// 全部の引数をプレースホルダーにする
		std::for_each(v.begin(), v.end(), bind(foo, _1, _1, _1));
			// 3,3,3
			// 1,1,1
			// 4,4,4
	}
	std::cout << "----" << std::endl;

	{
		std::vector<int> v;

		v.push_back(3);
		v.push_back(1);
		v.push_back(4);
		// 関数ポインタ
		for_each(v.begin(), v.end(), bind(&func, _1));

		// 関数オブジェクト
		for_each(v.begin(), v.end(), bind(functor(), _1));

		// メンバ関数ポインタ
		hoge h;
		for_each(v.begin(), v.end(), bind(&hoge::func, &h, _1));
	}
	std::cout << "----" << std::endl;

	{
		std11::function<int(int)> f = bind(add, 3, _1);
		std::cout << f(2) << std::endl; // add(3, 2);
	}
	std::cout << "----" << std::endl;

	{
		// bool (*)(int)
		std11::function<bool (int)> func = bind(is_even, _1);

		for (int i = 0; i < 10; ++i)
		{
			std::cout << "func(" << i << ") = " << std::boolalpha << func(i) << std::endl;
		}
	}

	
	return 0;
}
