/*
 * algorithmTest.cpp
 *
 *  Created on: 2014/02/25
 *      Author: Haruki Nakayama
 */

#include "gtest/gtest.h"

#include "stdlib.h"
#include "time.h"

#include <vector>
#include <functional>
#include "std11/algorithm.hpp"
#include "std11/numeric.hpp"
#include "std11/utility.hpp"

template <typename INT_T>
static bool is_even(INT_T value)
{
	return (value & 0x1) == 0;
}

template <typename INT_T>
static bool is_odd(INT_T value)
{
	return !is_even(value);
}

// TODO use <random> interface
static int rand_even()
{
	return rand() & (std::numeric_limits<int>::max() - 1);
}

static int rand_odd()
{
	return rand() | 0x1;
}

// class for mutating sequence operation std11::move
class movee
{
	bool moved_;
public:
	movee(void): moved_(false) {}
	movee(STD11_RV_REF(movee) source): moved_(true) {}

	static bool is_moved(movee const& m) { return m.moved_; }
};

class AlgorithmTest: public ::testing::Test
{
public:
	static size_t const VECTOR_SIZE = 100u;
	static unsigned const TEST_TRIES = 1000u;

protected:
	typedef std::vector<int> Vector;
	Vector evens_;
	Vector odds_;
	Vector mixed_;

	typedef Vector::iterator iterator_type;
	typedef Vector::value_type value_type;

	typedef bool (*pred_type)(value_type);
	static pred_type is_even_;
	static pred_type is_odd_;

	typedef bool (*test_type)(iterator_type, iterator_type, pred_type);
	static test_type all_of_;
	static test_type any_of_;
	static test_type none_of_;

public:
	AlgorithmTest():
		evens_(VECTOR_SIZE, 0),
		odds_(VECTOR_SIZE, 0),
		mixed_(VECTOR_SIZE, 0)
	{
	}

	void SetUp(void)
	{
		srand((unsigned)time(NULL));

		std::generate(evens_.begin(), evens_.end(), rand_even);
		std::generate(odds_.begin(), odds_.end(), rand_odd);
		std::generate(mixed_.begin(), mixed_.end() - 2, rand);
		mixed_[98] = rand_odd();
		mixed_[99] = rand_even();
	}
	void TearDown(void)
	{}
};

TEST_F(AlgorithmTest, NonMutatingOperations_AllOf)
{
	// all_of, is_even
	ASSERT_TRUE (all_of_(evens_.begin(), evens_.end(), is_even_));
	ASSERT_FALSE(all_of_(odds_.begin(),  odds_.end(),  is_even_));
	ASSERT_FALSE(all_of_(mixed_.begin(), mixed_.end(), is_even_));

	// all_of, is_odd
	ASSERT_FALSE(all_of_(evens_.begin(), evens_.end(), is_odd_));
	ASSERT_TRUE (all_of_(odds_.begin(),  odds_.end(),  is_odd_));
	ASSERT_FALSE(all_of_(mixed_.begin(), mixed_.end(), is_odd_));
}

TEST_F(AlgorithmTest, NonMutatingOperations_AnyOf)
{
	// any_of, is_even
	ASSERT_TRUE (any_of_(evens_.begin(), evens_.end(), is_even_));
	ASSERT_FALSE(any_of_(odds_.begin(),  odds_.end(),  is_even_));
	ASSERT_TRUE (any_of_(mixed_.begin(), mixed_.end(), is_even_));

	// any_of, is_odd
	ASSERT_FALSE(any_of_(evens_.begin(), evens_.end(), is_odd_));
	ASSERT_TRUE (any_of_(odds_.begin(),  odds_.end(),  is_odd_));
	ASSERT_TRUE (any_of_(mixed_.begin(), mixed_.end(), is_odd_));
}

TEST_F(AlgorithmTest, NonMutatingOperations_NoneOf)
{
	// none_of, is_even
	ASSERT_FALSE(none_of_(evens_.begin(), evens_.end(), is_even_));
	ASSERT_TRUE (none_of_(odds_.begin(),  odds_.end(),  is_even_));
	ASSERT_FALSE(none_of_(mixed_.begin(), mixed_.end(), is_even_));

	// none_of, is_odd
	ASSERT_TRUE (none_of_(evens_.begin(), evens_.end(), is_odd_));
	ASSERT_FALSE(none_of_(odds_.begin(),  odds_.end(),  is_odd_));
	ASSERT_FALSE(none_of_(mixed_.begin(), mixed_.end(), is_odd_));
}

TEST_F(AlgorithmTest, NonMutatingOperations_FindNotIf)
{
	// find_if_not, is_even
	ASSERT_EQ(std::find_if(evens_.begin(), evens_.end(), is_odd_),
		std11::find_if_not(evens_.begin(), evens_.end(), is_even_));
	ASSERT_EQ(std::find_if(odds_.begin(), odds_.end(), is_odd_),
		std11::find_if_not(odds_.begin(), odds_.end(), is_even_));
	ASSERT_EQ(std::find_if(mixed_.begin(), mixed_.end(), is_odd_),
		std11::find_if_not(mixed_.begin(), mixed_.end(), is_even_));

	// find_if_not, is_odd
	ASSERT_EQ(std::find_if(evens_.begin(), evens_.end(), is_even_),
		std11::find_if_not(evens_.begin(), evens_.end(), is_odd_));
	ASSERT_EQ(std::find_if(odds_.begin(), odds_.end(), is_even_),
		std11::find_if_not(odds_.begin(), odds_.end(), is_odd_));
	ASSERT_EQ(std::find_if(mixed_.begin(), mixed_.end(), is_even_),
		std11::find_if_not(mixed_.begin(), mixed_.end(), is_odd_));
}

TEST_F(AlgorithmTest, MutatingOperations_CopyN)
{
	// copy_n
	for (unsigned i = 0; i < TEST_TRIES; ++i)
	{
		Vector dest(VECTOR_SIZE, 0);
		size_t copy_size = static_cast<size_t>(rand()) % VECTOR_SIZE;
		iterator_type copy_tail = std11::copy_n(odds_.begin(), copy_size, dest.begin());

		ASSERT_TRUE(std::equal(dest.begin(), copy_tail, odds_.begin()));
		ASSERT_TRUE(std::equal(copy_tail, dest.end(), odds_.begin() + copy_size,
				std::not_equal_to<Vector::value_type>()));
	}
}

TEST_F(AlgorithmTest, MutatingOperations_CopyIf)
{
	for (unsigned i = 0; i < TEST_TRIES; ++i)
	{
		Vector dest(VECTOR_SIZE, 0);
		iterator_type copy_tail = std11::copy_if(mixed_.begin(), mixed_.end(),
				dest.begin(), is_odd_);

		ASSERT_TRUE(all_of_(dest.begin(), copy_tail, is_odd_));
		ASSERT_EQ(std::count_if(mixed_.begin(), mixed_.end(), is_odd_),
				std::distance(dest.begin(), copy_tail));
	}
}

TEST_F(AlgorithmTest, MutatingOperations_Move)
{
	for (unsigned i = 0; i < TEST_TRIES; ++i)
	{
		std::vector<movee> src(VECTOR_SIZE);
		std::vector<movee> dest(VECTOR_SIZE);
		size_t move_size = static_cast<size_t>(rand()) % VECTOR_SIZE;

		std::vector<movee>::iterator moved_tail =
				std11::move(src.begin(), src.begin() + move_size, dest.begin());
		ASSERT_EQ(move_size, static_cast<size_t>(std::distance(dest.begin(), moved_tail)));
		ASSERT_TRUE(std11::all_of(dest.begin(), dest.begin() + move_size,
				movee::is_moved));
		ASSERT_TRUE(std11::none_of(dest.begin() + move_size, dest.end(),
				movee::is_moved));
	}
}

TEST_F(AlgorithmTest, MutatingOperations_MoveBackward)
{
	for (unsigned i = 0; i < TEST_TRIES; ++i)
	{
		std::vector<movee> src(VECTOR_SIZE);
		std::vector<movee> dest(VECTOR_SIZE);
		size_t move_size = static_cast<size_t>(rand()) % VECTOR_SIZE;

		std::vector<movee>::iterator moved_head =
				std11::move_backward(src.begin(), src.begin() + move_size, dest.end());
		ASSERT_EQ(move_size, static_cast<size_t>(std::distance(moved_head, dest.end())));
		ASSERT_TRUE(std11::none_of(dest.begin(), moved_head, movee::is_moved));
		ASSERT_TRUE(std11::all_of(moved_head, dest.end(), movee::is_moved));
	}
}

TEST_F(AlgorithmTest, MutatingOperations_Shuffle)
{
	// TODO write test after "std11/random.hpp" implemented
}

TEST_F(AlgorithmTest, MutatingOperations_IsPartitioned)
{
	std::partition(mixed_.begin(), mixed_.end(), is_even_);

	ASSERT_TRUE(std11::is_partitioned(mixed_.begin(), mixed_.end(), is_even_));
}

TEST_F(AlgorithmTest, MutatingOperations_PartitionCopy)
{
	Vector evens;
	Vector odds;

	std11::partition_copy(mixed_.begin(), mixed_.end(),
			std::back_inserter(evens), std::back_inserter(odds), is_even_);
	ASSERT_EQ(mixed_.size(), evens.size() + odds.size());
	ASSERT_TRUE(all_of_(evens.begin(), evens.end(), is_even_));
	ASSERT_TRUE(all_of_(odds.begin(), odds.end(), is_odd_));
}

TEST_F(AlgorithmTest, MutatingOperations_PartitionPoint)
{
	std::partition(mixed_.begin(), mixed_.end(), is_even_);
	ASSERT_TRUE(std11::is_partitioned(mixed_.begin(), mixed_.end(), is_even_));

	iterator_type mid =
			std11::partition_point(mixed_.begin(), mixed_.end(), is_even_);
	ASSERT_TRUE(all_of_(mixed_.begin(), mid, is_even_));
	ASSERT_TRUE(none_of_(mid, mixed_.end(), is_even_));
}

TEST_F(AlgorithmTest, Sorts_IsSorted)
{
	std::sort(mixed_.begin(), mixed_.end());
	ASSERT_TRUE(std11::is_sorted(mixed_.begin(), mixed_.end()));

	std::random_shuffle(mixed_.begin(), mixed_.end());

	std::sort(mixed_.begin(), mixed_.end(), std::greater<value_type>());
	ASSERT_TRUE(std11::is_sorted(mixed_.begin(), mixed_.end(), std::greater<value_type>()));
}

TEST_F(AlgorithmTest, Sorts_IsSortedUntil)
{
	for (unsigned i = 0; i < TEST_TRIES; ++i)
	{
		size_t sort_range = static_cast<size_t>(rand()) % VECTOR_SIZE;

		std::partial_sort(mixed_.begin(), mixed_.begin() + sort_range, mixed_.end());
		ASSERT_LE(static_cast<iterator_type::difference_type>(sort_range),
				std::distance(mixed_.begin(),
						std11::is_sorted_until(mixed_.begin(), mixed_.end())));

		std::random_shuffle(mixed_.begin(), mixed_.end());

		std::partial_sort(mixed_.begin(), mixed_.begin() + sort_range, mixed_.end(),
				std::greater<value_type>());
		ASSERT_LE(static_cast<iterator_type::difference_type>(sort_range),
				std::distance(mixed_.begin(),
						std11::is_sorted_until(mixed_.begin(), mixed_.end(), std::greater<value_type>())));
	}
}

TEST_F(AlgorithmTest, Heaps_IsHeap)
{
	std::make_heap(mixed_.begin(), mixed_.end());
	ASSERT_TRUE(std11::is_heap(mixed_.begin(), mixed_.end()));

	std::random_shuffle(mixed_.begin(), mixed_.end());

	std::make_heap(mixed_.begin(), mixed_.end(), std::less<value_type>());
	ASSERT_TRUE(std11::is_heap(mixed_.begin(), mixed_.end(), std::less<value_type>()));
}

TEST_F(AlgorithmTest, Heaps_IsHeapUntil)
{
	for (unsigned i = 0; i < TEST_TRIES; ++i)
	{
		size_t sort_range = static_cast<size_t>(rand()) % VECTOR_SIZE;

		std::make_heap(mixed_.begin(), mixed_.begin() + sort_range);
		ASSERT_LE(static_cast<iterator_type::difference_type>(sort_range),
				std::distance(mixed_.begin(),
						std11::is_heap_until(mixed_.begin(), mixed_.end())));

		std::random_shuffle(mixed_.begin(), mixed_.end());

		std::make_heap(mixed_.begin(), mixed_.begin() + sort_range,
				std::greater<value_type>());
		ASSERT_LE(static_cast<iterator_type::difference_type>(sort_range),
				std::distance(mixed_.begin(),
						std11::is_heap_until(mixed_.begin(), mixed_.end(), std::greater<value_type>())));
	}
}

TEST_F(AlgorithmTest, MinMax)
{
	{
		int x = rand(), y = rand();

		std::pair<int const&, int const&> min_max_pair = std11::minmax(x, y);
		ASSERT_TRUE(min_max_pair.first <= min_max_pair.second);
		ASSERT_EQ(min_max_pair.first, std::min(x, y));
		ASSERT_EQ(min_max_pair.second, std::max(x, y));
	}
	{
		int x = rand(), y = rand();
		std11::greater<int> greater;

		std::pair<int const&, int const&> min_max_pair = std11::minmax(x, y, greater);
		ASSERT_FALSE(!greater(min_max_pair.first, min_max_pair.second));
		ASSERT_EQ(min_max_pair.first, std::min(x, y, greater));
		ASSERT_EQ(min_max_pair.second, std::max(x, y, greater));
	}
}

TEST_F(AlgorithmTest, MinMaxElement)
{
	{
		std::pair<iterator_type, iterator_type> min_max_pair =
				std11::minmax_element(mixed_.begin(), mixed_.end());

		ASSERT_TRUE(*min_max_pair.first <= *min_max_pair.second);
		ASSERT_EQ(*min_max_pair.first, *std::min_element(mixed_.begin(), mixed_.end()));
		ASSERT_EQ(*min_max_pair.second, *std::max_element(mixed_.begin(), mixed_.end()));
	}
	{
		std11::greater<iterator_type::value_type> greater;
		std::pair<iterator_type, iterator_type> min_max_pair =
				std11::minmax_element(mixed_.begin(), mixed_.end(), greater);

		ASSERT_FALSE(!greater(*min_max_pair.first, *min_max_pair.second));
		ASSERT_EQ(*min_max_pair.first, *std::min_element(mixed_.begin(), mixed_.end(), greater));
		ASSERT_EQ(*min_max_pair.second, *std::max_element(mixed_.begin(), mixed_.end(), greater));
	}
}

AlgorithmTest::pred_type AlgorithmTest::is_even_ = ::is_even<Vector::value_type>;
AlgorithmTest::pred_type AlgorithmTest::is_odd_ = ::is_odd<Vector::value_type>;

AlgorithmTest::test_type AlgorithmTest::all_of_ = std11::all_of<iterator_type, pred_type>;
AlgorithmTest::test_type AlgorithmTest::any_of_ = std11::any_of<iterator_type, pred_type>;
AlgorithmTest::test_type AlgorithmTest::none_of_ = std11::none_of<iterator_type, pred_type>;


