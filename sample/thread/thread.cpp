#include "std11/thread.hpp"

#include <unistd.h>
#include <stdio.h>

#define COUNT 5

std11::hash<std11::thread::id> hash;

int print10(void)
{
	for (unsigned i = 0; i < COUNT; ++i)
	{
		printf("[%08x] i = %u\n", hash(std11::this_thread::get_id()), i);
		sleep(1);
	}
	return 0;
}

int print10_multi(int multiplier)
{
	for (unsigned i = 0; i < COUNT; ++i)
	{
		printf("[%08x] i * %d = %d\n",
			hash(std11::this_thread::get_id()), multiplier, i*multiplier);
		sleep(1);
	}
	return 0;
}

int overloaded(void)
{
	return print10_multi(1);
}

int overloaded(int multi)
{
	return print10_multi(multi);
}

void modify(int& target, int m)
{
	target *= m;
}

class Print10
{
public:
	int operator()(void)
	{
		return print10();
	}

	int operator()(int multiplier)
	{
		return print10_multi(multiplier);
	}

	int member_function()
	{
		for (unsigned i = 0; i < COUNT; ++i)
		{
			printf("[%08x](member_function) this = %p, i = %u\n", 
				hash(std11::this_thread::get_id()), this, i);
			sleep(1);
		}
	return 0;
		
	}
};



int main()
{
	printf("hardware_concurrency() = %u\n", 
		std11::thread::hardware_concurrency());

	Print10 p;

	std11::thread t1(&print10);
	std11::thread t1_1(print10);
	std11::thread t2(print10_multi, 4);
	std11::thread t3(p);
	std11::thread t4;
	std11::function<int(void)> f = std11::bind(overloaded);
	
	std11::thread t4_1(f);
	std11::thread t4_2(std11::bind(overloaded, 20));

	std11::function<int(int)> f2
		= std11::bind(overloaded, std11::placeholders::_1);
	std11::thread t4_3(f2, 33);

	printf("Before moved:\n");
	printf("  hash(t2.get_id()) = %08x\n", hash(t2.get_id()));
	printf("  hash(t3.get_id()) = %08x\n", hash(t3.get_id()));
	printf("  hash(t4.get_id()) = %08x\n", hash(t4.get_id()));

	sleep(2);

	t4 = std11::move(t2);
	std11::thread t5(std11::move(t3));

	printf("After moved : t2 -> t4, t3 -> t5\n");
	printf("  hash(t2.get_id()) = %08x\n", hash(t2.get_id()));
	printf("  hash(t3.get_id()) = %08x\n", hash(t3.get_id()));
	printf("  hash(t4.get_id()) = %08x\n", hash(t4.get_id()));
	printf("  hash(t5.get_id()) = %08x\n", hash(t5.get_id()));

	int i1 = 100;
	int i2 = 200;
	std11::thread t6_byval(modify, i1, 20);
	std11::thread t6_byref(modify, std11::ref(i2), 20);

	std11::thread t7(&Print10::member_function, &p);
	std11::thread t7_1(&Print10::member_function, p);
	printf("&p = %p\n", &p);

	t2.detach();
	t1.join();
	t1_1.join();
	t3.join();
	t4.join();
	t4_1.join();
	t4_2.join();
	t4_3.join();
	t5.join();
	t6_byval.join();
	t6_byref.join();
	t7.join();
	t7_1.join();

	printf("i1 = %d, i2 = %d\n", i1, i2);

	return 0;
}

