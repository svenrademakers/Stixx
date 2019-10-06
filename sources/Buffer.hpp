#pragma once
#include <cassert>
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
	
	protected:
		T* data()
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
		  , MemoryView<T>(this->data(), N)
		  {}
		  
		Buffer(Buffer&) = delete;
		Buffer& operator=(Buffer&) = delete;

		constexpr Buffer(std::initializer_list<T> init)
			: Storage<T, N>()
			, MemoryView<T>(this->data(), N)
		{
			assert(init.size() <= N);

			auto storageit = this->begin();
			for (int i= 0; i < init.size(); ++i)
				new (storageit++) T(*(init.begin() + i));
		}
	};
}
