include(../cmake_helpers/AddMicroTest.cmake)
file(GLOB_RECURSE tests *Test.cpp *Test.hpp mocks/*)
AddMicroTest(Stixx ${tests})

SET(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Disable gtest for benchmark")
file(GLOB_RECURSE bench *Benchmark.cpp)
AddBenchmark(Stixx ${bench})