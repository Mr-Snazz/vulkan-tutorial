#include "vulkan/vertex.hpp"

VkVertexInputBindingDescription SNZ::Vertex::GetBindingDescription()
{
    VkVertexInputBindingDescription BindingDescription{};

    BindingDescription.binding = 0u;
    BindingDescription.stride = sizeof(SNZ::Vertex);
    BindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return BindingDescription;
}

std::array<VkVertexInputAttributeDescription, 3u> SNZ::Vertex::GetAttributeDescriptions()
{
    std::array<VkVertexInputAttributeDescription, 3u> AttributeDescriptions{};

    AttributeDescriptions[0].binding = 0u;
    AttributeDescriptions[0].location = 0u;
    AttributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
    AttributeDescriptions[0].offset = offsetof(SNZ::Vertex, SNZ::Vertex::Position);

    AttributeDescriptions[1].binding = 0u;
    AttributeDescriptions[1].location = 1u;
    AttributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    AttributeDescriptions[1].offset = offsetof(SNZ::Vertex, SNZ::Vertex::Color);

    AttributeDescriptions[2].binding = 0u;
    AttributeDescriptions[2].location = 2u;
    AttributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
    AttributeDescriptions[2].offset = offsetof(SNZ::Vertex, SNZ::Vertex::TextureCoordinate);

    return AttributeDescriptions;
}



SNZ::Vertex::Vertex(const glm::vec2& IPosition, const glm::vec3& IColor, const glm::vec2& ITextureCoordinate)
    : Position(IPosition), Color(IColor), TextureCoordinate(ITextureCoordinate)
{

}