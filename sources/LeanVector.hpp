#pragma once
#include "MemoryView.hpp"

namespace sx
{
	template<class T>
	class StorageHolder
	{
	public:
		StorageHolder() = default;
		StorageHolder(StorageHolder&) = delete;
		StorageHolder& operator=(StorageHolder&) = delete;

		using StorageType = T;

	protected:
		StorageType storage;
	};

	template<class Base, std::size_t MaxSize_>
	class StackStorage
		: public StorageHolder<std::array<typename Base::value_type, MaxSize_>>
		, public Base
	{
	public:
		constexpr StackStorage()
			: Base(storage.data(), storage.data() + storage.size())
		{}
	};

	template <class T>
	class LeanVector
	{
	public:
		using value_type = T;

		template <std::size_t MaxSize>
		using WithStorage = StackStorage<LeanVector<T>, MaxSize>;

		constexpr LeanVector()
			: range(nullptr, nullptr)
			, current(nullptr)
		{}

		constexpr LeanVector(T* begin, T* end)
			: range(begin, end)
			, current(begin)
		{}

		operator const T &() const
		{
			return range;
		}

		LeanVector& operator=(const LeanVector& other)
		{
			this->current = other.current;
			this->range = other.range;
		}

		T& operator[](uint32_t index)
		{
			assert(index < size());
			return *(range.begin() + index);
		}

		constexpr std::size_t size()
		{
			return current - range.begin();
		}

		constexpr std::size_t max_size()
		{
			return range.size();
		}

		constexpr void pop_back()
		{
			assert(current > range.begin());
			--current;
		}

		constexpr void push_back(const T& value)
		{
			assert(current < range.end());
			*current = value;
			++current;
		}
		 
	private:
		MemoryView<T> range;
		T* current;
	};
}

