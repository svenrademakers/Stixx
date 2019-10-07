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

template<class T, class Bind>
struct BinAdapter
{
	static_assert(std::is_member_pointer<Bind>::value, "only memberpointers allowed.");

	constexpr BinAdapter(Bind abind)
		: bind(abind)
	{}

	auto operator()(T& val)
	{
		return std::bind(bind, std::placeholders::_1)(val);
	}

private:
	Bind bind;
};

template<class T>
struct BinAdapter<T, void*>
{
	constexpr BinAdapter(void *) {}

	T& operator()(T& val)
	{
		return val;
	}
};

template<class T, class Bind = void*>
void SvenSort(const sx::MemoryView<T> collection, Bind bind = nullptr)
{
	if (collection.size() == 1)
		return;

	std::size_t firstUnsortedIndex = 1;
	BinAdapter<T,Bind> f(bind);

	do
	{
		std::size_t index = firstUnsortedIndex;
		while (index > 0)
		{
			if (f(collection[index]) < f(collection[index - 1]))
				std::swap(collection[index], collection[index - 1]);
			--index;
		}
	} while (++firstUnsortedIndex < collection.size());
}

