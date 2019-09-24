// tests.cpp
#include <gtest/gtest.h>
#include "Buffer.hpp"

int main(int argc, char **argv) {
	sx::Buffer<int,2> wat;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
