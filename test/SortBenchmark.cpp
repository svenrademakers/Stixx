#include <benchmark/benchmark.h>
#include "Sort.h"
#include <vector>
#include <fstream> 
#include <iostream>

static std::vector<char> GetTestData()
{
	std::ifstream file("C:\\git\\Stixx\\test\\Random_5MB.bin", std::ios::binary);
	return std::vector<char>((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());
}
static std::vector<char> TestData = GetTestData();

static void BM_BubbleSort(benchmark::State& state) 
{
	std::vector<char> TestSet = TestData;
	sx::MemoryView<char> range(TestSet.data(), state.range(0));
	for (auto _ : state) 
		BubbleSort(range);
}

BENCHMARK(BM_BubbleSort)->DenseRange(6400, 30464, 128);
//BENCHMARK(BM_BubbleSort)->RangeMultiplier(2)->Range(0, 1<<16);

