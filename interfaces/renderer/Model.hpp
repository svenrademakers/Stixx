#ifndef MODEL_HPP
#define MODEL_HPP

#include <glm/glm.hpp>

namespace sx
{
	class Model
	{
	public:
		virtual ~Model() {};
		virtual void UpdateModelMatrix(const glm::mat4& matrix) = 0;
	};
}
#endif
