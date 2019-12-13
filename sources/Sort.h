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
	static bool toggle = true;

	template<class T>
	void ToggleBuffers(sx::MemoryView<T>& a,
		sx::MemoryView<T>& b,
		sx::MemoryView<T>*& from,
		sx::MemoryView<T>*& to)
	{

		if (toggle)
		{
			from = &a;
			to = &b;
		}
		else
		{
			from = &b;
			to = &a;
		}

		toggle = !toggle;
	}

	template<class T>
	void WriteBack(sx::MemoryView<T>& to,
		sx::MemoryView<T>& from)
	{
		if (!toggle)
			std::memcpy(to.begin(), from.begin(), from.size()* sizeof(T));
	}

	template<class T>
	void Merge(T* left, T* right, const int size, T* result)
	{
		int i = 0;
		T* leftIt = left;
		T* rightIt = right;

		while (leftIt != left + size && rightIt != right + size)
		{
			if (*leftIt > *rightIt)
			{
				result[i] = *rightIt;
				++rightIt;
			}
			else
			{
				result[i] = *leftIt;
				++leftIt;
			}
			++i;
		}

		while (leftIt != left + size)
		{
			result[i] = *leftIt;
			++i;
			++leftIt;
		}
		
		while (rightIt != right + size)
		{
			result[i] = *rightIt;
			++i;
			++rightIt;
		}
	}
}

template <class T>
void MergeSort(sx::MemoryView<T> collection)
{
	if (collection.size() < 2)
		return;

	std::vector<T> resultBuffer;
	resultBuffer.resize(collection.size());
	sx::MemoryView<T> extraBuffer(resultBuffer.data(), resultBuffer.size());

	int size = 1;
	sx::MemoryView<T>* from = nullptr;
	sx::MemoryView<T>* to = nullptr;

	for (int n = 0; n < collection.size() / 2; ++n)
	{
		ToggleBuffers(collection, extraBuffer, from, to);

		int write = 0;
		for (int i = 0; i < collection.size() / (size * 2); ++i)
		{
			Merge(from->begin()+ write, from->begin() + write + size, size, to->begin() + write);
			write += size*2;
		}
		size += size;
	}

	WriteBack(collection, extraBuffer);
}
