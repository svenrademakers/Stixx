#pragma once
#include <vector>
#include <cassert>
#include <array>
#include <iterator>

namespace sx
{
	template<class T>
	class MemoryView
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		constexpr MemoryView(const iterator begin, const iterator end)
			: beginElement(begin)
			, count(std::distance(begin, end))
		{}

		constexpr MemoryView(T* start, std::size_t length)
			: beginElement(start)
			, count(length)
		{}

		constexpr T& operator[](const std::size_t index) const
		{
			return *(beginElement + index);
		}

		constexpr iterator begin() const
		{
			return beginElement;
		}

		constexpr const_iterator cbegin() const
		{
			return beginElement;
		}

		constexpr iterator end() const
		{
			return beginElement + count;
		}

		constexpr const_iterator cend() const
		{
			return beginElement + count;
		}
		
		constexpr iterator last() const
		{
			assert(count > 0);
			return beginElement + count -1;
		}


		constexpr std::size_t size() const
		{
			return count;
		}

	private:
		const iterator beginElement;
		const std::size_t count;
	};
}
