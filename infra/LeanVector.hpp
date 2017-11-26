#ifndef LEAN_VECTOR_HPP
#define LEAN_VECTOR_HPP

#include "MemoryRange.hpp"

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

		LeanVector()
			: range(0,0)
			, current(nullptr)
		{}

		LeanVector(T* begin, T* end)
			: range(begin, end)
			, current(nullptr)
		{}

		constexpr std::size_t size()
		{
			return range.size();
		}
 
	private:
		MemoryRange<T> range;
	};
}

#endif 
