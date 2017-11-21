#ifndef IMAGE_OPERATION_HPP
#define IMAGE_OPERATION_HPP

#include <string>
#include <exception>
#include "utils/AlgorithmBilinear.hpp"
#include "interfaces/Image.hpp"

namespace sx
{
	class Image;
	class Algorithm;

	class ImageOperation
	{
	public:
		virtual ~ImageOperation() = default;
		virtual void Execute(Image& image) = 0;
	};

	class ImageOperationBilinear
		: public ImageOperation
	{
	public:
		ImageOperationBilinear() = default;
		virtual ~ImageOperationBilinear() = default;

		virtual void Execute(Image& image) override;

	private:
		const AlgorithmBilinear<4> algo32b;
		const AlgorithmBilinear<3> algo24b;
	};

	class ImageOperationTimer
		: public ImageOperation
	{
	public:
		ImageOperationTimer(ImageOperation& operation);
		virtual ~ImageOperationTimer() = default;

		virtual void Execute(Image& image) override;

	private:
		ImageOperation& operation;
	};
}

#endif
