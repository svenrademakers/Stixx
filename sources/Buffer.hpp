#pragma once

#include <initializer_list>
#include <type_traits>
#include "MemoryView.hpp"

namespace sx
{
	template<class T, std::size_t N, std::size_t Alignment>
	class AlignedStorage
	{
	public:
		using value_type = typename std::aligned_storage<sizeof(T), Alignment>::type;
		
		AlignedStorage() = default;
		AlignedStorage(AlignedStorage&) = delete;
		AlignedStorage& operator=(AlignedStorage&) = delete;

		value_type storage[N];
	};
	
	template<class T, std::size_t N, std::size_t Alignment = alignof(T)>
	class Buffer
		: public AlignedStorage<T,N,alignof(T)>
		, public MemoryView<T, typename AlignedStorage<T, N, Alignment>::value_type>
	{
	public:
		constexpr Buffer()
		  : AlignedStorage<T, N, alignof(T)>()
		  , MemoryView<T, AlignedStorage<T, N, Alignment>::value_type>(storage, N)
		  {}
		  
		Buffer(Buffer&) = delete;
		Buffer& operator=(Buffer&) = delete;

		constexpr Buffer(std::initializer_list<T> init)
			: AlignedStorage<T, N, alignof(T)>()
			, MemoryView<T, AlignedStorage<T, N, alignof(T)>::value_type>(storage, N)
		{
			assert(init.size() <= N && "size of initializer list too big.");

			iterator storageit = begin();
			for (std::initializer_list<T>::iterator it = init.begin(); it != init.end(); ++it)
			{
				new (&*storageit) T(*it);
				++storageit;
			}
		}
	};
}
