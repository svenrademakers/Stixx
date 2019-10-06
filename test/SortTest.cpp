#include <gtest/gtest.h>
#include "Sort.h"
#include "Buffer.hpp"
#include <functional>

static sx::Buffer<void(sx::MemoryView<int>), 1> sortFunctions()
{
	sx::Buffer<void(sx::MemoryView<int>), 1> wat;
	wat[0] = BubbleSort;
	return wat;
}
//		= { std::function<void(sx::MemoryView<int>)>(SelectionSort) };
//= {
//	BubbleSort
//};

//class SortingTests :
//	public testing::TestWithParam<int> {
//	// You can implement all the usual fixture class members here.
//	// To access the test parameter, call GetParam() from class
//	// TestWithParam<T>.
//};
//
//TEST_P(SortingTests, two_value_sort)
//{
//	sx::Buffer<int, 2> x = { 3,2 };
//
//	auto sortFunction = GetParam();
//	sortFunction(x);
//
//	EXPECT_EQ(x[0], 2);
//	EXPECT_EQ(x[1], 3);
//}
//
//TEST_P(SortingTests, sort_one_value)
//{
//	auto sortFunction = GetParam();
//
//	sx::Buffer<int, 1 > x = { 2 };
//
//	BubbleSort(x);
//	EXPECT_EQ(x[0], 2);
//}
//
//TEST_P(SortingTests, sort_with_negative_numbers)
//{
//	auto sortFunction = GetParam();
//
//	sx::Buffer<int, 4 > x = { 2,3,888888, -44 };
//	BubbleSort(x);
//	EXPECT_EQ(x[0], -44);
//	EXPECT_EQ(x[1], 2);
//	EXPECT_EQ(x[2], 3);
//	EXPECT_EQ(x[3], 888888);
//}
//
//INSTANTIATE_TEST_CASE_P(BubbleSortTest, 
//	SortingTests, 
//	::testing::Values(bubbleSortF));