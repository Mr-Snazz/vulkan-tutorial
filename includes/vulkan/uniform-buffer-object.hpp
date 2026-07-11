#pragma once

#include <glm/glm.hpp>

namespace SNZ
{
    class UniformBufferObject
    {
    public:
        glm::mat4 ModelMatrix, ViewMatrix, ProjectionMatrix;

        UniformBufferObject(const glm::mat4& IModelMatrix, const glm::mat4& IViewMatrix, const glm::mat4& IProjectionMatrix);

    private:


    };
}