#include "ImageTga.hpp"
#include <cassert>

namespace sx
{
	bool ImageTga::HasCompression() const
	{
		return header[2] & 0x1000;
	}

	Extent ImageTga::Resolution() const
	{
		uint32_t w = header[12] + (header[13] << 8);
		uint32_t h = header[14] + (header[15] << 8);
		return { w, h };
	}

	uint8_t ImageTga::PixelDepth() const
	{
		assert(AlphaDepth() == 0 || AlphaDepth() == header[16]);
		return header[16];
	}

	MemoryRange<uint8_t>& ImageTga::PixelBuffer()
	{
		return pixelBuffer;
	}

	void ImageTga::Resolution(const Extent& extent)
	{
		header[12] = (extent.width & 0xFF);
		header[13] = static_cast<uint8_t>(extent.width >> 8);
		header[14] = (extent.height & 0xFF);
		header[15] = static_cast<uint8_t>(extent.height >> 8);
	}

	uint8_t ImageTga::AlphaDepth() const
	{
		return header[17] & 0x07;
	}

	uint8_t ImageTga::ImageIdSize() const
	{
		return header[0];
	}

	uint16_t ImageTga::ColorMapSize() const
	{
		return header[5] + (header[6] << 8);
	}

	std::size_t ImageTga::PixelBufferSize() const
	{
		return Resolution().width * Resolution().height * PixelDepth() / 8;
	}

	void ImageTga::Load(std::istream& filestream)
	{
		filestream.read(reinterpret_cast<char*>(header.data()), header.size());
		imageId.resize(ImageIdSize());
		colorMap.resize(ColorMapSize());
		pixelStorage.resize(PixelBufferSize());

		filestream.read(reinterpret_cast<char*>(imageId.data()), imageId.size());
		filestream.read(reinterpret_cast<char*>(colorMap.data()), colorMap.size());
		filestream.read(reinterpret_cast<char*>(pixelStorage.data()), pixelStorage.size());
		pixelBuffer = MemoryRange<uint8_t>(pixelStorage);
	}

	void ImageTga::Save(std::ostream& filestream)
	{
		pixelStorage.resize(pixelBuffer.size());
		filestream.write(reinterpret_cast<char*>(header.data()), header.size());
		filestream.write(reinterpret_cast<char*>(imageId.data()), imageId.size());
		filestream.write(reinterpret_cast<char*>(colorMap.data()), colorMap.size());
		filestream.write(reinterpret_cast<char*>(pixelStorage.data()), pixelStorage.size());
	}
}
