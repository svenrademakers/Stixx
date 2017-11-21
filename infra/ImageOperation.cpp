#include <chrono>
#include <iostream>
#include "ImageOperation.hpp"
#include "interfaces/FileSystem.hpp"
#include "interfaces/Image.hpp"
#include "MemoryRange.hpp"

namespace sx
{
	void ImageOperationBilinear::Execute(Image& image)
	{
		uint8_t pixelDepth = image.PixelDepth();
		if (image.HasCompression() || (image.PixelDepth() != 24 && image.PixelDepth() != 32))
			throw std::exception("image not supported!..");

		MemoryRange2D<uint8_t> buffer(image.PixelBuffer(), image.Resolution().width);
		assert(buffer.size() > 0);

		if (pixelDepth == 24)
			algo24b.Execute(buffer);
		else
			algo32b.Execute(buffer);

		image.Resolution({ image.Resolution().width / 2, image.Resolution().height / 2 });
	}

	ImageOperationTimer::ImageOperationTimer(ImageOperation& operation)
		: operation(operation)
	{}

	void ImageOperationTimer::Execute(Image& image)
	{
		auto begin = std::chrono::high_resolution_clock::now();
		operation.Execute(image);
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
		std::cout << "Took " << duration << " microseconds to execute" << std::endl;
	}
}