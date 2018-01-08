#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <chrono>
#include "glm/glm.hpp"
#include "infra/Observer.hpp"

namespace sx
{
	class HotLoopObserver
		: public Observer<HotLoopObserver>
	{
	public:
		using Observer<HotLoopObserver>::Observer;
		virtual void Update(std::chrono::duration<float>& elapsedMs) = 0;
	};

	class Renderer
		: public Subject<HotLoopObserver>
	{
	public:
		virtual ~Renderer(){};
		virtual void Draw()  = 0;
	};

	class Buffer;

	enum BufferType
	{
		TransferSrc = 0x1,
		TransferDst = 0x2,
		Uniform = 0x10,
		Indices = 0x40,
		VertexData = 0x80
	};

	class ViewProjectionMatrix
	{
	public:
		virtual void TransformView(const glm::mat4&& transformation) = 0;
		virtual void TransformProjection(const glm::mat4&& transformation) = 0;
	};
}

#endif
