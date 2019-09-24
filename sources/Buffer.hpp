#pragma once
#include <initializer_list>
#include "MemoryView.hpp"

namespace sx
{
	template<class T, std::size_t N>
	class StackStorage
	{
	public:
		constexpr StackStorage() = default;
		StackStorage(StackStorage&) = delete;
		StackStorage& operator=(StackStorage&) = delete;

		T * data()
		{
			return internalBuffer;
		}

	private:
		T internalBuffer[N];
	};

	template<class T, std::size_t N>
	class Storage
		: public StackStorage<T,N>
		, public MemoryView<T>
	{
	public:
		constexpr Storage()
			: StackStorage<T,N>()
			, MemoryView<T>(this)
		{}
	};

	template<class T, std::size_t N>
	class Buffer 
		: public Storage<T, N>
	{
	public:
		Buffer() = default;
		Buffer(Buffer&) = delete;
		Buffer& operator=(Buffer&) = delete;

		constexpr Buffer(std::initializer_list<T> init)
		{
			assert(init.size() <= N);

			MemoryView<T>::iterator storageit = this->begin();
			for (std::initializer_list<T>::iterator it = init.begin(); it != init.end(); ++it)
				*storageit++ = *it;
		}
	};
}
