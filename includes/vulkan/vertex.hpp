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
        static VkVertexInputBindingDescription GetBindingDescription();

        static std::array<VkVertexInputAttributeDescription, 3u> GetAttributeDescriptions();

    public:
        glm::vec3 Position;
        glm::vec3 Color;
        glm::vec2 TextureCoordinate;

        Vertex(const glm::vec3& IPosition, const glm::vec3& IColor, const glm::vec2& TextureCoordinate);

    private:


    };
}

