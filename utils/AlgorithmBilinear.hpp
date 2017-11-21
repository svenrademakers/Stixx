#ifndef ALGORITHM_BILINEAR_HPP
#define ALGORITHM_BILINEAR_HPP

#include "infra/MemoryRange.hpp"
#include "infra/StridedIterator.hpp"

namespace sx
{
	constexpr uint8_t InterpolateValue(uint8_t val1, uint8_t val2)
	{
		return (val1 / 2) + (val2 / 2) + (val1 & val2 & 1);
	}

	template<uint32_t Stride_, class InputIt1, class InputIt2, class OutputIt>
	void BilinearTransform(InputIt1 first1, InputIt1 last1, InputIt2 first2, OutputIt d_first)
	{
		for (auto iter = first1; iter != last1; ++iter)
		{
			*first1 = InterpolateValue(*first1, *(first1 + Stride_));
			*first2 = InterpolateValue(*first2, *(first2 + Stride_));
			*d_first = InterpolateValue(*first1, *first2);

			++first1;
			++first2;
			++d_first;
		}
	}

	template<uint32_t Stride_>
	class AlgorithmBilinear
	{
	public:
		using Iterator = StridedIterator<uint8_t, Stride_>;
		using Iterator2D = StridedIterator2D<uint8_t, Stride_>;


		void Execute(MemoryRange2D<uint8_t>& buffer) const
		{
			Iterator output(buffer.begin());
			const Iterator end(buffer.begin() + buffer.size() / 4);
			assert(buffer.size() >= buffer.width() * 2 * Iterator::Stride);
			assert(!(buffer.width() & 1));

			Iterator2D column(buffer.begin(), buffer.width());
			Iterator2D contiguesColumn(buffer.begin(), buffer.width());
			contiguesColumn.verticalIncrement();

			while (output != end)
			{
				auto columnEnd = column + buffer.width();
				while (column != columnEnd)
				{
					BilinearTransform<Stride_>(&*column, &*column + Stride_, &*contiguesColumn, &*output);
					column += 2;
					contiguesColumn += 2;
					++output;
				}

				column.verticalIncrement();
				contiguesColumn.verticalIncrement();
			}

			buffer.shrink(buffer.size() / 4);
		}
	};
}
#endif
