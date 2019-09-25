#pragma once
#include <initializer_list>
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

		constexpr Buffer(std::initializer_list<T> init)
		{
			assert(init.size() <= N);

			iterator storageit = this->begin();
			for (std::initializer_list<T>::iterator it = init.begin(); it != init.end(); ++it)
				*storageit++ = *it;
		}
	};
}
