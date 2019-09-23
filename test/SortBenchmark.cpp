#include <benchmark/benchmark.h>
#include "Sort.h"
#include <array>
#include <string>
#include <stdlib.h>
#include <time.h> 
#include <vector>

#define RUN_DATASET(sortFunction, testset) BENCHMARK_CAPTURE(BM_##sortFunction, testset, testset);

template<class T, std::size_t size>
static std::array<std::vector<T>, size> GenerateTestData(uint32_t stepsize)
{
	std::array<std::vector<T>, size> data;
	for (int i = 0; i < size; ++i)
	{
		std::vector<T> result;
		result.reserve(i+1);

		srand((unsigned int)time(NULL));

		for (int ii = 0; ii < i+1; ++ii)
		{
			T random = rand() % std::numeric_limits<T>::max();
			result.push_back(random);
		}

		data[i] = result;
	}
	return data;
}

static auto TestSet = GenerateTestData<int, 2000>(2);

#define DECLARE_BM_FUNCTION(sortfunction, type)\
static void BM_##sortfunction(benchmark::State& state) { \
	for (auto _ : state) sortfunction(TestSet[0]);}

//DECLARE_BM_FUNCTION(BubbleSort, int);

//RUN_DATASET(BubbleSort, testSet1)
//RUN_DATASET(BubbleSort, testSet2)
