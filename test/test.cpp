// tests.cpp
#include <gtest/gtest.h>
#include "Buffer.hpp"
#include "Sort.h"

int main(int argc, char **argv) {
	sx::Buffer<int, 8> wat{ 6, 3, 2, 4, 1, 8, 5, 7 };

	MergeSort(wat);
	

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
