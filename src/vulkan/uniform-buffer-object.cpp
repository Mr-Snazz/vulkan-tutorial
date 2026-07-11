#include "vulkan/uniform-buffer-object.hpp"

SNZ::UniformBufferObject::UniformBufferObject(const glm::mat4& IModelMatrix, const glm::mat4& IViewMatrix, const glm::mat4& IProjectionMatrix)
    : ModelMatrix(IModelMatrix), ViewMatrix(IViewMatrix), ProjectionMatrix(IProjectionMatrix)
{

}