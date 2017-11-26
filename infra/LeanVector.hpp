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

	template<class Base, class StorageType>
	class StackStorage
		: public StorageHolder<StorageType>
		, public Base
	{
	public:
		StackStorage()
			: Base(storage.data(), storage.data() + storage.size())
		{}
	};

	template <class T>
	class LeanVector
	{
	public:
		template <std::size_t MaxSize>
		using WithStorage = StackStorage<LeanVector<T>, std::array<uint8_t, MaxSize>>;

		LeanVector()
			: range(0,0)
		{}

		LeanVector(typename const MemoryRange<T>::iterator begin, 
			typename const MemoryRange<T>::iterator end)
			: range(begin, end)
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
