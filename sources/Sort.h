#pragma once
#include <cstdlib>
#include "MemoryView.hpp"

template <class T, class Predicate>
inline void BubbleSort(const sx::MemoryView<T>& collection, const Predicate& predicate)
{
	T temp;
	bool sorted = false;

	for (int i = 0; i < collection.size(); ++i)
	{
		sorted = true;
		for (int ii = 0; ii < collection.size(); ++ii)
		{
			if (ii + 1 < collection.size() && predicate(collection[ii], collection[ii + 1]))
			{
				temp = collection[ii];
				collection[ii] = collection[ii + 1];
				collection[ii + 1] = temp;
				sorted = false;
			}
		}

		if (sorted)
			break;
	}
}

template <class T>
void BubbleSort(const sx::MemoryView<T>& collection)
{
	BubbleSort(collection, [](const T& first, const T& second) { return first > second; });
}

template <class T, std::size_t N>
void SelectionSort(T(&collection)[N])
{
	for (int i = 0; i < N; ++i)
	{
		std::size_t minSize;
		for (int ii = 0; ii < N; ++ii)
		{
			
		}
	}

}