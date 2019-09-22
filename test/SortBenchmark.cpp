#include <benchmark/benchmark.h>
#include "utils/Sort.h"
#include <thread>

static void BM_BubbleSort(benchmark::State& state) {
	int64_t x[4] = { 2,3,888888, -44 };

	for (auto _ : state)
		BubbleSort(x);
}
BENCHMARK(BM_BubbleSort);