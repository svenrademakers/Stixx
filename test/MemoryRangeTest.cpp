#include <gtest/gtest.h>
#include "MemoryView.hpp"
#include <vector>
#include "Buffer.hpp"

namespace sx
{
	TEST(MemoryRangeTest, sanity_check)
	{
		sx::Buffer<uint32_t, 3> range = { 1,2,3 };

		EXPECT_EQ(3, range.size());
		EXPECT_EQ(1, *range.begin());
		EXPECT_EQ(3, *(range.begin() + 2));

		auto iterator = range.begin();
		++iterator;
		EXPECT_EQ(2, *iterator);
	}

	TEST(MemoryRangeTest, MemoryRange2D)
	{
		sx::Buffer<uint32_t, 6> range = { 1,2,3,4,5,10 };

		EXPECT_EQ(6, range.size());
		EXPECT_EQ(1, *range.begin());
		EXPECT_EQ(5, *(range.begin() + 4));

		auto iterator = range.begin();
		++iterator;
		EXPECT_EQ(2, *iterator);
	}
}