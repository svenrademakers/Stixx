#pragma once
#include <cstdlib>
#include "MemoryView.hpp"

template <class T, class Predicate>
inline void BubbleSort(const sx::MemoryView<T>& collection, const Predicate& predicate)
{
	bool sorted = false;

	for (int i = 0; i < collection.size(); ++i)
	{
		sorted = true;
		for (int ii = 0; ii < collection.size(); ++ii)
		{
			if (ii + 1 < collection.size() && predicate(collection[ii], collection[ii + 1]))
			{
				std::swap(collection[ii], collection[ii+1]);
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

template <class T>
void SelectionSort(const sx::MemoryView<T>& collection)
{
	T min = 0;
	for (int i=0; i<collection.size(); ++i)
	{
		min = i;
		for (int ii = i; ii < collection.size(); ++ii)
		{
			if(collection[ii] < collection[min])
				min = ii;
		}
		std::swap(collection[i], collection[min]);
	}
}