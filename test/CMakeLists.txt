include(../cmake_helpers/AddMicroTest.cmake)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

SET(INSTALL_GTEST OFF CACHE BOOL "Disable gtest for benchmark")
SET(INSTALL_GMOCK OFF CACHE BOOL "Disable gmock for benchmark")

SET(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Disable gtest for benchmark")
SET(BENCHMARK_ENABLE_TESTING OFF CHACHE BOOL "disable benchmark tests")
file(GLOB_RECURSE tests *Test.cpp *Test.hpp mocks/*)
AddMicroTest(Stixx ${tests})


file(GLOB_RECURSE bench *Benchmark.cpp)
AddBenchmark(Stixx ${bench})