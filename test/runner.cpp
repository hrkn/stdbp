/*
 * runner.cpp
 *
 *  Created on: 2013/06/28
 *      Author: hrkn
 */

#include "gtest/gtest.h"

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
