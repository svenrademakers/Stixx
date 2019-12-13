#include <gtest/gtest.h>
#include "Sort.h"
#include "Buffer.hpp"
#include <functional>

template<class T>
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
		case 2:
			InsertionSort(view);
			break;
		case 3:
			//MergeSort(view);
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

//TEST_P(SortingTests, sortStructs)
//{
//	struct testStruct
//	{
//		long long a;
//		char b;
//		int mytestValue;
//	};
//
//	testStruct a, b, c, d;
//	a.mytestValue = 2;
//	b.mytestValue = 3;
//	c.mytestValue = 888888;
//	d.mytestValue = -44;
//
//	sx::Buffer<testStruct, 4 > x = {a, b, c, d};
//	auto sortFunction = GetParam();
//	ExeSortFunction(x, sortFunction);
//
//	EXPECT_EQ(x[0].mytestValue, -44);
//	EXPECT_EQ(x[1].mytestValue, 2);
//	EXPECT_EQ(x[2].mytestValue, 3);
//	EXPECT_EQ(x[3].mytestValue, 888888);
//}

INSTANTIATE_TEST_CASE_P(SortingTestSuite, 
	SortingTests, 
	::testing::Values(0,1,2));