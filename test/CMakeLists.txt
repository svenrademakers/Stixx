set(CURR_DIR ${CMAKE_CURRENT_LIST_DIR})  
include(AddMicroTest.cmake)

SET(INSTALL_GTEST OFF CACHE BOOL "Disable gtest for benchmark")
SET(INSTALL_GMOCK OFF CACHE BOOL "Disable gmock for benchmark")

SET(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Disable gtest for benchmark")
SET(BENCHMARK_ENABLE_TESTING OFF CHACHE BOOL "disable benchmark tests")

if(WIN32)
	SET(gtest_force_shared_crt on CACHE BOOL "Use shared (DLL) run-time lib even when Google Test is built as static lib.") 
endif()

add_subdirectory(${CURR_DIR}/googletest)
add_subdirectory(${CURR_DIR}/benchmark)

file(GLOB_RECURSE tests *Test.cpp *Test.hpp mocks/*)
AddMicroTest(Stixx ${tests})

file(GLOB_RECURSE bench *Benchmark.cpp)
AddBenchmark(Stixx ${bench})