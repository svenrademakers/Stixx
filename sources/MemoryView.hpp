#pragma once
#include <iterator>

namespace sx
{
	template<typename T, typename AlignedType>
	class MemoryView
	{
	public:
		class AlignedIterator
		{
		public:
			using value_type = T;
			using pointer = T * ;
			using reference = T & ;
			using difference_type = std::ptrdiff_t;
			using iterator_category = std::random_access_iterator_tag;

			AlignedIterator(AlignedType* data)
				: ptr(data)
			{}

			reference operator*()
			{
				return *reinterpret_cast<T*>(ptr);
			}

			const reference operator*() const
			{
				return *reinterpret_cast<T*>(ptr);
			}

			reference operator[](std::size_t size) const
			{
				return *reinterpret_cast<T*>(ptr + size);
			}

			pointer operator->()
			{
				return reinterpret_cast<T*>(ptr);
			}

			const pointer operator->() const
			{
				return reinterpret_cast<T*>(ptr);
			}

			AlignedIterator& operator++()
			{
				++ptr;
				return *this;
			}

			AlignedIterator operator++(int)
			{
				AlignedIterator r(*this);
				++ptr;
				return r;
			}

			AlignedIterator operator+(std::size_t n)
			{
				AlignedIterator r(*this);
				return ptr += n;
			}

		private:
			AlignedType * ptr = nullptr;
		};

		typedef typename AlignedIterator iterator;
		typedef typename const AlignedIterator const_iterator;

		constexpr MemoryView(iterator start, std::size_t length)
			: beginElement(start)
			, count(length)
		{}

		constexpr MemoryView(const iterator begin, const iterator end)
			: beginElement(begin)
			, count(std::distance(begin, end))
		{}

		constexpr T& operator[](const std::size_t index) const
		{
			return beginElement[index];
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
		iterator beginElement;
		const std::size_t count;
	};
}
