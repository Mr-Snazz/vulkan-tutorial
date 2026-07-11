#pragma once

#include <array>

#include <glm/glm.hpp>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace SNZ
{
    class Vertex
    {
    public:
        static inline VkVertexInputBindingDescription GetBindingDescription();

        static inline std::array<VkVertexInputAttributeDescription, 2u> GetAttributeDescriptions();

    public:
        glm::vec2 Position;
        glm::vec3 Color;

        Vertex(const glm::vec2& IPosition, const glm::vec3& IColor);

    private:


    };
}

#include "vulkan/vertex.inl"
