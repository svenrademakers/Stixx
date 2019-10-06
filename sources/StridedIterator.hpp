#ifndef STRIDED_ITERATOR_HPP
#define STRIDED_ITERATOR_HPP

#include <stdint.h>

namespace sx
{
	template<class T, uint32_t Stride_>
	class StridedIterator
	{
	public:
		typedef uint32_t difference_type;
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef std::input_iterator_tag iterator_category;
		static constexpr uint32_t Stride = Stride_;

	public:
		constexpr StridedIterator()
			: ptr(nullptr)
		{}

		constexpr StridedIterator(pointer rawPtr)
			: ptr(rawPtr)
		{}

		constexpr bool operator!=(const StridedIterator& other)
		{
			return !(*this == other);
		}

		constexpr bool operator==(const StridedIterator& other)
		{
			return ptr == other.ptr;
		}

		constexpr reference operator*()
		{
			return *ptr;
		}

		constexpr StridedIterator operator+(std::size_t n)
		{
			return StridedIterator(ptr + n*Stride_);
		}

		StridedIterator& operator++()
		{
			ptr += Stride_;
			return *this;
		}

		StridedIterator& operator+=(const std::size_t size)
		{
			ptr += size*Stride_;
			return *this;
		}

	protected:
		pointer ptr;
	};

	template<class T, uint32_t Stride_>
	class StridedIterator2D
		: public StridedIterator<T, Stride_>
	{
	public:
		StridedIterator2D(const StridedIterator<T, Stride_> iterator, const uint32_t width)
			: StridedIterator<T, Stride_>(iterator)
			, width(width)
		{}

		void verticalIncrement()
		{
			this->ptr += (Stride_ * width);
		}

	private:
		const uint32_t width;
	};
}
#endif