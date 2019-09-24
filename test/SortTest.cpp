#include <gtest/gtest.h>
#include "Sort.h"
#include "Buffer.hpp"

TEST(bubbleSortTest, two_value_sort)
{
	sx::Buffer<int, 2> x = { 3,2 };

	BubbleSort(x);
	EXPECT_EQ(x[0], 2);
	EXPECT_EQ(x[1], 3);
}

TEST(bubbleSortTest, two_value_sort_decending)
{
	sx::Buffer<int, 2 > x = { 2,3 };

	BubbleSort(sx::MemoryView<int>(x), [](const char& first, const char& second) { return first < second; });
	EXPECT_EQ(x[0], 3);
	EXPECT_EQ(x[1], 2);
}

TEST(bubbleSortTest, one_value)
{
	sx::Buffer<int, 1 > x = { 2 };

	BubbleSort(x);
	EXPECT_EQ(x[0], 2);
}

TEST(bubbleSortTest, sort_multiple_values)
{
	sx::Buffer<int, 4 > x = { 2,3,888888, -44 };
	BubbleSort(x);
	EXPECT_EQ(x[0], -44);
	EXPECT_EQ(x[1], 2);
	EXPECT_EQ(x[2], 3);
	EXPECT_EQ(x[3], 888888);
}