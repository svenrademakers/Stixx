#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cstdint>
#include <istream>
#include <vector>
#include "MemoryRange.hpp"

namespace sx
{
	struct Extent
	{
		uint32_t width;
		uint32_t height;
	};

	class Image
	{
	public:
		virtual ~Image() = default;

		virtual bool HasCompression() const = 0;
		virtual Extent Resolution() const = 0;
		virtual void Resolution(const Extent& extent) = 0;
		virtual uint8_t PixelDepth() const = 0;

		virtual MemoryRange<uint8_t>& PixelBuffer() = 0;
	};
}

#endif