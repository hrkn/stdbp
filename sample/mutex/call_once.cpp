#include <iostream>
#include "std11/thread.hpp"
#include "std11/mutex.hpp"

std11::once_flag once;

void init(int i)
{
	// 初期化を行う...
	std::cout << "initialize " << i << std::endl;
}

void thread_proc(int i)
{
	std11::call_once(once, init, i);
}

int main()
{
	std::cout << "<<>>" << std::endl;
	std11::thread t1(thread_proc, 100);
	std11::thread t2(thread_proc, 200);
	std11::thread t3(thread_proc, 300);

	t1.join();
	t2.join();
	t3.join();
	std::cout << ">><<" << std::endl << std::endl;
}

