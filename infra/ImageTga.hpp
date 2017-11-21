#ifndef IMAGE_TGA_HPP
#define IMAGE_TGA_HPP

#include <array>
#include <vector>
#include "interfaces/Image.hpp"
#include "interfaces/FileSystem.hpp"

namespace sx
{
	class ImageTga
		: public Image
		, public File
	{
	public:
		ImageTga() = default;
		virtual ~ImageTga() = default;
		ImageTga(const ImageTga&) = delete;
		ImageTga& operator=(const ImageTga&) = delete;

		bool HasCompression() const override;
		Extent Resolution() const override;
		void Resolution(const Extent& extent) override;

		uint8_t PixelDepth() const override;
		MemoryRange<uint8_t>& PixelBuffer() override;

		void Load(std::istream& filestream) override;
		void Save(std::ostream& filestream) override;

	private:
		uint8_t AlphaDepth() const;
		uint8_t ImageIdSize() const;
		uint16_t ColorMapSize() const;
		std::size_t PixelBufferSize() const;

	private:
		std::array<uint8_t, 18> header;
		std::vector<uint8_t> imageId;
		std::vector<uint8_t> colorMap;
		std::vector<uint8_t> pixelStorage;
		MemoryRange<uint8_t> pixelBuffer;
	};
}

#endif