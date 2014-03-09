/*
 * utilityTest.cpp
 *
 *  Created on: 2013/07/15
 *      Author: Haruki Nakayama
 */
#include <time.h>
#include <stdlib.h>

#include "gtest/gtest.h"

#include "std11/utility.hpp"
#include "std11/functional.hpp"

class Movable
{
	int value_;
public:
	Movable(void) :
			value_(int())
	{
	}
	Movable(int value) :
			value_(value)
	{
	}
	Movable(STD11_RV_REF(Movable) source): value_()
	{
		std::swap(value_, source.instance.value_);
	}

	Movable& operator=(STD11_RV_REF(Movable) source)
	{
		std::swap(value_, source.instance.value_);
		return *this;
	}

	int getValue(void)
	{
		return value_;
	}
};

#define RANDOM(MIN, MAX)  rand()%(MAX-MIN+1)+MIN;

class UtilityTest: public ::testing::Test
{
public:
	int VALUE;

	void SetUp(void)
	{
		// TODO shuold be have more smaller granularity randomness
		srand((unsigned) time(NULL) + VALUE);
		VALUE = RANDOM(0, 65535);
	}
	void TearDown(void)
	{
	}
};

TEST_F(UtilityTest, DISABLED_CompilationError)
{
	// Statement below occurs compilation error
	//int i = std11::move(int(5));
}

TEST_F(UtilityTest, MoveConstruction)
{
	Movable src(VALUE);
	EXPECT_EQ(VALUE, src.getValue());

	Movable dest(std11::move(src));
	EXPECT_EQ(VALUE, dest.getValue());
	EXPECT_NE(VALUE, src.getValue());
}

TEST_F(UtilityTest, MoveConstructionFromTempObject)
{
	Movable dest(std11::move(Movable(VALUE)));
	EXPECT_EQ(VALUE, dest.getValue());
}

TEST_F(UtilityTest, MoveAssignment)
{
	Movable src(VALUE);
	EXPECT_EQ(VALUE, src.getValue());

	Movable dest;
	EXPECT_EQ(int(), dest.getValue());
	dest = std11::move(src);
	EXPECT_EQ(VALUE, dest.getValue());
}

TEST_F(UtilityTest, MoveAssignmentFromTempObject)
{
	Movable dest;
	EXPECT_EQ(int(), dest.getValue());
	dest = std11::move(Movable(VALUE));
	EXPECT_EQ(VALUE, dest.getValue());
}

TEST_F(UtilityTest, MakePair)
{
	{
		int x = 1, y = 2;
		std11::pair<int&, int> p = std11::make_pair(std11::ref(x), y);

		ASSERT_EQ(x, p.first);
		ASSERT_EQ(y, p.second);
		x = 10, y = 20;
		ASSERT_EQ(x, p.first);
		ASSERT_NE(y, p.second);
		ASSERT_EQ(2, p.second);
	}
}
