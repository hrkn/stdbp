/*
 * cstddefTest.cpp
 *
 *  Created on: 2014/03/08
 *      Author: Haruki Nakayama
 */

#include "gtest/gtest.h"

#define STDBP_FORCE_DEFINE_ORIGINAL_OFFSETOF
#include "std11/cstddef.hpp"

class CstddefTest: public ::testing::Test
{
public:
};

TEST_F(CstddefTest, OffsetOf)
{
	struct test_struct
	{
		int first;
		long long int second;
		char third[8];
	};

#ifdef STDBP_HAS_ORIGINAL_OFFSETOF
	ASSERT_EQ(0u, offsetof(test_struct, first));
	ASSERT_EQ(sizeof(int), offsetof(test_struct, second));
	ASSERT_EQ(sizeof(int) + sizeof(long long int), offsetof(test_struct, third));
#endif
}

TEST_F(CstddefTest, NullPtr)
{
	ASSERT_EQ(sizeof(void*), sizeof(std11::nullptr_t));
}
