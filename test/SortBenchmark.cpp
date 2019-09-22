#include <benchmark/benchmark.h>
#include "utils/Sort.h"
#include <array>
#include <string>
#include <stdlib.h>
#include <time.h> 

#define RUN_DATASET(sortFunction, testset) BENCHMARK_CAPTURE(BM_##sortFunction, testset, testset);
#define DECLARE_BM_FUNCTION(sortfunction) template <class ...ExtraArgs> \
static void BM_##sortfunction(benchmark::State& state, ExtraArgs&&... extra_args) { \
	std::tuple<ExtraArgs...> parameters(extra_args...); auto testSet = std::get<0>(parameters); \
	for (auto _ : state) sortfunction(testSet);}

template<class T, std::size_t size>
static std::array<T, size> GenerateTestData()
{
	std::array<T, size> result;
	srand((unsigned int)time(NULL));

	T random = rand() % std::numeric_limits<T>::max();
	for (int i = 0; i < size; ++i)
		result[i] = random;
	return result;
}

static std::array<int, 4> testSet1 = { 2,3,888888, -44 };
static auto testSet2 = GenerateTestData<int, 2000>();

DECLARE_BM_FUNCTION(BubbleSort)
RUN_DATASET(BubbleSort, testSet1)
RUN_DATASET(BubbleSort, testSet2)
