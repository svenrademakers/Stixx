#include <gtest/gtest.h>
#include "MemoryView.hpp"
#include <vector>

namespace sx
{
	TEST(MemoryRangeTest, sanity_check)
	{
		std::vector<uint32_t> storage = { 1,2,3 };
		MemoryView<uint32_t> range(storage);

		EXPECT_EQ(3, range.size());
		EXPECT_EQ(1, *range.begin());
		EXPECT_EQ(3, *(range.begin() + 2));

		auto iterator = range.begin();
		++iterator;
		EXPECT_EQ(2, *iterator);
	}

	TEST(MemoryRangeTest, MemoryRange2D)
	{
		std::vector<uint32_t> storage = { 1,2,3,4,5,10 };
		MemoryView<uint32_t> range(storage);

		EXPECT_EQ(6, range.size());
		EXPECT_EQ(1, *range.begin());
		EXPECT_EQ(5, *(range.begin() + 4));

		auto iterator = range.begin();
		++iterator;
		EXPECT_EQ(2, *iterator);
	}
}