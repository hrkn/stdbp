#include <iostream>
#include <std11/functional.hpp>

using namespace std;
using namespace std11;

void say_hello()
{
	cout << "Hello" << endl;
}

bool is_even(int value)
{
	return value % 2 == 0;
}

struct display_object
{
	void operator()(int value, double pi) const
	{
		cout << "disp_obj(" << value << ", " << pi << ")" << endl;
	}
};

class A
{
public:
	int hoge()
	{
		return 42;
	}

	static int static_func()
	{
		return 4242;
	}
};

int main()
{
	// void (*)(void)
	function<void(void)> func0 = say_hello;
	func0(); // disp_hello(); ... Hello

	// bool (*)(int)
	function<bool(int)> func1 = is_even;
	cout << "result of func1(2) = " << func1(2) << endl; // is_even(2);

	// 関数オブジェクト
	function<void(int, double)> func_obj = display_object();
	func_obj(5, 3.14); // disp_obj::operator(5, 3.14);

	// メンバ関数
	A obj;
	function<int(A*)> member_function = &A::hoge;
	cout << "obj.hoge() = " << member_function(&obj) << endl;

	// 静的メンバ関数
	function<int()> static_member_function = &A::static_func;
	cout << "A::static_func() = " << static_member_function() << endl;

	// 関数が未割当のfunctionオブジェクト実行
	function<void()> f;
	try
	{
		f();
	}
	catch (std11::bad_function_call const&)
	{
		cout << "bad function call!" << endl;
	}

	return 0;
}

