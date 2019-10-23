#pragma once
#include <functional>
#include <type_traits>
#include <cassert>
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
void BubbleSort(const sx::MemoryView<T> collection)
{
	BubbleSort(collection, [](const T& first, const T& second) { return first > second; });
}

template <class T>
void SelectionSort(const sx::MemoryView<T> collection)
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

template <class T>
void InsertionSort(const sx::MemoryView<T> collection)
{
	if (collection.size() == 1)
		return;

	std::size_t firstUnsortedIndex = 1;
	
	do
	{
		std::size_t index = firstUnsortedIndex;
		while (index > 0)
		{
			if (collection[index] < collection[index - 1])
				std::swap(collection[index], collection[index - 1]);
			--index;
		}
	} while (++firstUnsortedIndex < collection.size());
}

namespace
{
	template<class T>
	void RecursiveMerge(const sx::MemoryView<T> collection, const sx::MemoryView<T> result)
	{
		std::size_t size = collection.size();
		if (size == 1)
			return;
		else if (size == 2)
		{
			if (*collection.begin() > *collection.last())
				std::swap(*collection.begin(), *collection.last());
		}
		else
		{
			const sx::MemoryView<T>& left{ collection.begin(), collection.begin() + (size / 2) };
			const sx::MemoryView<T>& right{ collection.begin() + (size / 2), collection.end() };
			RecursiveMerge<T>(left, {result.begin(), result.begin() + (size/2)});
			RecursiveMerge<T>(right, { result.begin() + (size / 2), result.begin() });

			T* l = left.begin();
			T* r = right.begin();
			T* n = result.begin();
			for (int i = 0; i < result.size(); i)
			{
				if (r == right.end() || *l < *r)
				{
					*n = *l;
					++l;
				}
				else 
				{
					*n = *r;
					++r;
				}
				++n;
			}
		}
	}
}

template <class T>
void MergeSort(const sx::MemoryView<T>& collection)
{
	std::vector<T> resultBuffer;
	resultBuffer.reserve(collection.size());

	const sx::MemoryView<T> result(&*resultBuffer.begin(), resultBuffer.size());
	RecursiveMerge<T>(collection, result);
	memcpy(collection.begin(), &*resultBuffer.begin(), collection.size());
}
