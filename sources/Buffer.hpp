#pragma once
#include <initializer_list>
#include <type_traits>
#include "MemoryView.hpp"

namespace sx
{
	template<class T, std::size_t N>
	class Storage
	{
	public:
		using value_type = typename std::decay<T>::type;
		constexpr Storage() = default;
		Storage(Storage&) = delete;
		Storage& operator=(Storage&) = delete;
	
	protected:
		value_type* data()
		{
			return internalBuffer;
		}

	private:
		value_type internalBuffer[N];
	};

	template<class T, std::size_t N>
	class Buffer 
		: public Storage<T, N>
		, public MemoryView<Storage<T, N>::value_type>
	{
	public:			  
		Buffer(Buffer&) = delete;
		Buffer& operator=(Buffer&) = delete;
		
		constexpr Buffer()
		  : Storage<T,N>()
		  , MemoryView<Storage<T, N>::value_type>(this->data(), N)
		  {}

		constexpr Buffer(std::initializer_list<T> init)
			: Storage<T, N>()
			, MemoryView<Storage<T, N>::value_type>(this->data(), N)
		{
			assert(init.size() <= N);

			auto storageit = this->begin();
			for (int i= 0; i < init.size(); ++i)
				new (storageit++) T(*(init.begin() + i));
		}
	};
}
