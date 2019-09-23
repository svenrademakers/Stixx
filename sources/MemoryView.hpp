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
		typedef typename T* iterator;
		typedef typename const T* const_iterator;

		template<typename T2, std::size_t N>
		constexpr MemoryView(const std::array<T2, N>& arr)
			: beginElement(arr.data())
			, endElement(arr.data() + arr.size())
			, count(arr.size())
		{}

		MemoryView(std::vector<T>& vector)
			: beginElement(vector.data())
			, count(vector.size())
		{}

		constexpr MemoryView(const iterator begin, const iterator end)
			: beginElement(begin)
			, count(std::distance(begin, end))
		{}

		constexpr MemoryView(T* start, std::size_t length)
			: beginElement(start)
			, size(length)
		{}

		constexpr T& operator[](const std::size_t index) const
		{
			return *const_cast<T*>(beginElement + index);
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

		constexpr std::size_t size() const
		{
			return count;
		}

	private:
		const iterator beginElement;
		const std::size_t count;
	};
}