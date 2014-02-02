/*
 * threadTest.cpp
 *
 *  Created on: 2013/06/28
 *      Author: hrkn
 */
#include <unistd.h>

#include "gtest/gtest.h"

#include "std11/thread.hpp"

// Worker functions for testing
static void dummy_function(void)
{
	// nothing to do
}

static void pass_by_val(int i)
{
	i += 10;
}

static void pass_by_ref(int& i)
{
	i += 10;
}

class ThreadTest: public ::testing::Test
{
public:
	void SetUp(void)
	{
		::testing::GTEST_FLAG(death_test_style) = "threadsafe";
	}
	void TearDown(void) {}
};

typedef ThreadTest ThreadDeathTest;

TEST_F(ThreadTest, InactiveThread)
{
	std11::thread empty;

	EXPECT_EQ(std11::thread::id(), empty.get_id());
	EXPECT_FALSE(empty.joinable());
	empty.join();  // no effects
	empty.detach();  // no effects
	EXPECT_FALSE(empty.joinable());
}

TEST_F(ThreadTest, ActiveThread)
{
	{
		std11::thread t(dummy_function);
		ASSERT_NE(t.get_id(), std11::thread::id());
		ASSERT_TRUE(t.joinable());

		t.join();
		ASSERT_EQ(t.get_id(), std11::thread::id());
		ASSERT_FALSE(t.joinable());
	}

	{
		std11::thread t(dummy_function);
		ASSERT_NE(t.get_id(), std11::thread::id());
		ASSERT_TRUE(t.joinable());

		t.detach();
		ASSERT_EQ(t.get_id(), std11::thread::id());
		ASSERT_FALSE(t.joinable());

		// To avoid segfault caused by "rapid destruction"
		// (see also comment near the thread::procedure_)
		usleep(30000);
	}
}

TEST_F(ThreadTest, ArgPassingVariation)
{
	{
		// pass_by_ref: not using ref
		int a = 4;
		std11::thread t(pass_by_ref, a);
		ASSERT_NE(t.get_id(), std11::thread::id());
		t.join();
		ASSERT_EQ(4, a);
	}
	{
		// pass_by_ref: using ref
		int a = 4;
		std11::thread t(pass_by_ref, std11::ref(a));
		EXPECT_NE(t.get_id(), std11::thread::id());
		t.join();
		ASSERT_EQ(14, a);
	}
	{
		// pass_by_val: not using ref
		int a = 4;
		std11::thread t(pass_by_val, a);
		ASSERT_NE(t.get_id(), std11::thread::id());
		t.join();
		ASSERT_EQ(4, a);
	}
	{
		// pass_by_val: using ref
		int a = 4;
		std11::thread t(pass_by_val, std11::ref(a));
		EXPECT_NE(t.get_id(), std11::thread::id());
		t.join();
		ASSERT_EQ(4, a);
	}
}

TEST_F(ThreadTest, Swap)
{
	std11::thread t1(dummy_function);
	std11::thread::id t1_id = t1.get_id();

	std11::thread t2(dummy_function);
	std11::thread::id t2_id = t2.get_id();

	t1.swap(t2);
	EXPECT_EQ(t1_id, t2.get_id());
	EXPECT_EQ(t2_id, t1.get_id());

	EXPECT_TRUE(t1.joinable());
	EXPECT_TRUE(t2.joinable());

	t1.join();
	t2.join();
}

TEST_F(ThreadTest, Move)
{
	{
		// move construction
		std11::thread src(dummy_function);
		std11::thread::id src_id = src.get_id();
		ASSERT_NE(std11::thread::id(), src_id);
		ASSERT_TRUE(src.joinable());

		std11::thread dest(std11::move(src));
		ASSERT_NE(src_id, src.get_id());
		ASSERT_EQ(src_id, dest.get_id());
		ASSERT_FALSE(src.joinable());
		ASSERT_TRUE(dest.joinable());
		dest.join();
	}
	{
		// move assignment
		std11::thread src(dummy_function);
		std11::thread::id src_id = src.get_id();
		ASSERT_NE(std11::thread::id(), src_id);
		ASSERT_TRUE(src.joinable());

		std11::thread dest;
		ASSERT_EQ(std11::thread::id(), dest.get_id());
		dest = std11::move(src);
		ASSERT_NE(src_id, src.get_id());
		ASSERT_EQ(src_id, dest.get_id());
		ASSERT_FALSE(src.joinable());
		ASSERT_TRUE(dest.joinable());
		dest.join();
	}
	{
		// move assignment of temporary object
		std11::thread dest;
		ASSERT_EQ(std11::thread::id(), dest.get_id());
		ASSERT_FALSE(dest.joinable());
		dest = std11::move(std11::thread(dummy_function));
		ASSERT_TRUE(dest.joinable());
		dest.join();
	}
}

TEST_F(ThreadTest, ThreadId)
{
	std11::hash<std11::thread::id> h;

	{
		std11::thread::id this_thread_id(std11::this_thread::get_id());
		ASSERT_EQ((size_t)pthread_self(), h(this_thread_id));
	}
	{
		// Identical copy
		std11::thread t(dummy_function);
		std11::thread::id tid_from_object(t.get_id());
		std11::thread::id tid_from_value(h(t.get_id()));

		EXPECT_EQ(tid_from_object, tid_from_value);

		t.join();
	}
}

TEST_F(ThreadTest, Yield)
{
	std11::this_thread::yield();
	SUCCEED();
}

TEST_F(ThreadTest, HardwareConcurrency)
{
	unsigned int concurrency = std11::thread::hardware_concurrency();
	std::cout << "Hardware concurrency = " << concurrency << std::endl;
	SUCCEED();
}

TEST_F(ThreadDeathTest, UnjoinedThread)
{
	ASSERT_DEATH({ std11::thread t(dummy_function); }, "");
}
