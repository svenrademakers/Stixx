#include <gtest/gtest.h>
#include "StridedIterator.hpp"

namespace sx
{
	TEST(StridedIteratorTest, increment_iterator)
	{
		std::vector<uint8_t> storage = { 1, 5, 8, };
		StridedIterator<uint8_t, 1> it(storage.data());
		EXPECT_EQ(1, *it);
		EXPECT_EQ(5, *(it + 1));
		EXPECT_EQ(5, *(++it));
		EXPECT_EQ(8, *(it += 1));
	}

	TEST(StridedIteratorTest, increment_strided_iterator)
	{
		std::vector<uint8_t> storage = { 1, 5, 8, 6, 4, 5, 8, 6 };
		StridedIterator<uint8_t, 2> it(storage.data());
		EXPECT_EQ(1, *it);
		EXPECT_EQ(8, *(it + 1));
		EXPECT_EQ(8, *(++it));
		EXPECT_EQ(4, *(it += 1));
	}

	TEST(StridedIteratorTest, compare_iterator)
	{
		std::vector<uint8_t> storage = { 1, 5, 8, };
		StridedIterator<uint8_t, 1> it(storage.data());
		StridedIterator<uint8_t, 1> it2(storage.data());

		EXPECT_TRUE(it == it2);
		EXPECT_FALSE(it != it2);
		++it2;
		EXPECT_TRUE(it != it2);
		EXPECT_FALSE(it == it2);
	}

	TEST(StridedIteratorTest, compare_strided_iterator)
	{
		std::vector<uint8_t> storage = { 1, 5, 8, 39 };
		StridedIterator<uint8_t, 2> it(storage.data());
		StridedIterator<uint8_t, 2> it2(storage.data());

		EXPECT_TRUE(it == it2);
		EXPECT_FALSE(it != it2);
		++it2;
		EXPECT_TRUE(it != it2);
		EXPECT_FALSE(it == it2);
	}
}