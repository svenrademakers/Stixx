#include <gtest/gtest.h>
#include "utils/Sort.h"

TEST(bubbleSortTest, two_value_sort)
{
	char x[2] = { 3,2 };

	BubbleSort(x);
	EXPECT_EQ(x[0], 2);
	EXPECT_EQ(x[1], 3);
}

TEST(bubbleSortTest, two_value_sort_decending)
{
	char x[2] = { 2,3 };

	BubbleSort(x, [](const char& first, const char& second) { return first < second; });
	EXPECT_EQ(x[0], 3);
	EXPECT_EQ(x[1], 2);
}

TEST(bubbleSortTest, one_value)
{
	char x[1] = { 2 };

	BubbleSort(x);
	EXPECT_EQ(x[0], 2);
}

TEST(bubbleSortTest, sort_multiple_values)
{
	int64_t x[4] = { 2,3,888888, -44 };

	BubbleSort(x);
	EXPECT_EQ(x[0], -44);
	EXPECT_EQ(x[1], 2);
	EXPECT_EQ(x[2], 3);
	EXPECT_EQ(x[3], 888888);
}