#pragma once
#include <cassert>
#include "MemoryView.hpp"

namespace sx
{
	template<class T, std::size_t N>
	class Storage
	{
	public:
		constexpr Storage() = default;
		Storage(Storage&) = delete;
		Storage& operator=(Storage&) = delete;

		T * data()
		{
			return internalBuffer;
		}

	private:
		T internalBuffer[N];
	};

	template<class T, std::size_t N>
	class Buffer 
		: public Storage<T, N>
		, public MemoryView<T>
	{
	public:
		constexpr Buffer()
		  : Storage<T,N>()
		  , MemoryView<T>(this)
		  {}
		  
		Buffer(Buffer&) = delete;
		Buffer& operator=(Buffer&) = delete;

		template<class T2, std::size_t N2>
		constexpr Buffer(const T2 (&init)[N2])
		{
			static_assert(N2 <= N, "assignment does not fit buffer!");

			iterator storageit = this->begin();
			for (int i= 0; i < N2; ++i)
				*storageit++ = init[i];
		}
	};
}
