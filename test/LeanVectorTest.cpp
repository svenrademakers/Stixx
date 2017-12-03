#ifndef LEAN_VECTOR_TEST_HPP
#define LEAN_VECTOR_TEST_HPP

#include <array>
#include "gtest/gtest.h"
#include "infra/LeanVector.hpp"

namespace sx
{
	TEST(LeanVectorTest, size)
	{
		LeanVector<uint8_t> size;
		EXPECT_EQ(0, size.size());
		struct st
		{
			std::array<uint64_t,12> arr;
		};

		LeanVector<st>::WithStorage<2> size2;
		EXPECT_EQ(0, size2.size());
		EXPECT_EQ(2, size2.max_size());
	}

	TEST(LeanVectorTest, push_and_pop)
	{
		LeanVector<uint8_t>::WithStorage<22> leanVec;
		leanVec.push_back(2);
		leanVec.push_back(3);

		EXPECT_EQ(2, leanVec[0]);
		EXPECT_EQ(3, leanVec[1]);

		EXPECT_EQ(2, leanVec.size());
		EXPECT_EQ(22, leanVec.max_size());
		leanVec.pop_back();
		EXPECT_EQ(1, leanVec.size());
		EXPECT_EQ(22, leanVec.max_size());
	}

	TEST(LeanVectorTest, assignment_copy_operator)
	{
		LeanVector<uint8_t>::WithStorage<22> leanVec;
		leanVec.push_back(2);
		leanVec.push_back(3);

		LeanVector<uint8_t> vector2 = leanVec;

		EXPECT_EQ(vector2.size(), 2);
		EXPECT_EQ(vector2.max_size(), 22);
		EXPECT_EQ(vector2[0], leanVec[0]);
		EXPECT_EQ(vector2[1], leanVec[1]);

		vector2.push_back(5);
	}
}
#endif