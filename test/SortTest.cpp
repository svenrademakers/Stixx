#include <gtest/gtest.h>
#include "Sort.h"
#include "Buffer.hpp"
#include <functional>

template<typename T>
void ExeSortFunction(const sx::MemoryView<T>& view, int index)
{
	switch(index)
	{
		case 0:
			BubbleSort(view);
			break;
		case 1:
			SelectionSort(view);
			break;

		default:
			std::cout << "sort function index unknown";
			break;
	}
}

class SortingTests :
	public testing::TestWithParam<int> {
	// You can implement all the usual fixture class members here.
	// To access the test parameter, call GetParam() from class
	// TestWithParam<T>.
};

TEST_P(SortingTests, two_value_sort)
{
	sx::Buffer<int, 2> x = { 3,2 };

	auto sortFunction = GetParam();
	ExeSortFunction(x, sortFunction);

	EXPECT_EQ(x[0], 2);
	EXPECT_EQ(x[1], 3);
}

TEST_P(SortingTests, sort_one_value)
{
	sx::Buffer<int, 1 > x = { 2 };

	auto sortFunction = GetParam();
	ExeSortFunction(x, sortFunction);
	
	EXPECT_EQ(x[0], 2);
}

TEST_P(SortingTests, sort_with_negative_numbers)
{
	sx::Buffer<int, 4 > x = { 2,3,888888, -44 };
	auto sortFunction = GetParam();
	ExeSortFunction(x, sortFunction);
	
	EXPECT_EQ(x[0], -44);
	EXPECT_EQ(x[1], 2);
	EXPECT_EQ(x[2], 3);
	EXPECT_EQ(x[3], 888888);
}

INSTANTIATE_TEST_CASE_P(SortingTestSuite, 
	SortingTests, 
	::testing::Values(0,1));