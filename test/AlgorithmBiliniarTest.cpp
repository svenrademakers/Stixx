#include <gtest/gtest.h>
#include <vector>
#include <array>
#include "utils/AlgorithmBilinear.hpp"
#include "infra/MemoryRange.hpp"
#include "interfaces/Image.hpp"

namespace sx
{
	TEST(InterPolationTest, interpolate)
	{
		EXPECT_EQ(12, InterpolateValue(20, 4));
	}

	TEST(InterPolationTest, interpolating_boundries)
	{
		EXPECT_EQ(0, InterpolateValue(0, 0));
		EXPECT_EQ(0xFF, InterpolateValue(-1, -1));
		EXPECT_EQ(0xFE, InterpolateValue(0xFF, 0xFE));
	}

	TEST(InterPolationTest, interpolate_2_odd_samples)
	{
		EXPECT_EQ(4, InterpolateValue(1, 8));
		EXPECT_EQ(5, InterpolateValue(5, 6));
		EXPECT_EQ(5, InterpolateValue(3, 7));
	}

	TEST(linearInterPolationTest, bilinear_interpolating_zero)
	{
		AlgorithmBilinear<1> algo;
		std::vector<uint8_t> storage = { 0, 0, 0, 0 };
		MemoryRange2D<uint8_t> buffer(storage, 2);
		algo.Execute(buffer);

		EXPECT_EQ(0, *storage.begin());
		EXPECT_EQ(1, buffer.size());
	}

	TEST(linearInterPolationTest, bilinear_interpolating_max)
	{
		AlgorithmBilinear<1> algo;
		std::vector<uint8_t> storage = { 0xFF, 0xFF, 0xFF, 0xFF };
		MemoryRange2D<uint8_t> buffer(storage, 2);
		algo.Execute(buffer);

		EXPECT_EQ(0xFF, *storage.begin());
		EXPECT_EQ(1, buffer.size());
	}

	TEST(linearInterPolationTest, bilinear_interpolating_arbritrary)
	{
		AlgorithmBilinear<1> algo;
		std::vector<uint8_t> storage = { 1, 5, 8, 6 };
		MemoryRange2D<uint8_t> buffer(storage, 2);
		algo.Execute(buffer);

		EXPECT_EQ(5, storage[0]);
		EXPECT_EQ(1, buffer.size());
	}

	TEST(BilinearInterPolationTest, bilinear_interpolating_stride_multiple_lines)
	{
		AlgorithmBilinear<2> algo;
		std::vector<uint8_t> storage = { 1,  5, 8, 6,  1,  5,  8, 6,
										 9, 12, 3, 7, 49, 22, 40, 10,
										13, 14, 1, 2,  7,  8,  3,  2,
										 1,  5, 8, 6,  1,  5,  8, 6 };

		MemoryRange2D<uint8_t> buffer(storage, 4);
		algo.Execute(buffer);

		EXPECT_EQ(8, buffer.size());
		EXPECT_EQ(5, storage[0]);
		EXPECT_EQ(7, storage[1]);
		EXPECT_EQ(24, storage[2]);
		EXPECT_EQ(10, storage[3]);
		EXPECT_EQ(5, storage[4]);
		EXPECT_EQ(6, storage[5]);
		EXPECT_EQ(4, storage[6]);
		EXPECT_EQ(5, storage[7]);
	}

	TEST(BilinearInterPolationTest, bilinear_interpolating_multiple_lines)
	{
		AlgorithmBilinear<1> algo;
		std::vector<uint8_t> storage = { 1, 5, 8, 6, 1, 5, 8, 6, 1, 5, 8, 6, 1, 5, 8, 6 };
		MemoryRange2D<uint8_t> buffer(storage, 4);
		algo.Execute(buffer);

		EXPECT_EQ(4, buffer.size());
		EXPECT_EQ(3, storage[0]);
		EXPECT_EQ(7, storage[1]);
		EXPECT_EQ(3, storage[2]);
		EXPECT_EQ(7, storage[3]);
	}
}