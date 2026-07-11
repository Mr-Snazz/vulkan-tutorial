#include "vulkan/vertex.hpp"

inline VkVertexInputBindingDescription SNZ::Vertex::GetBindingDescription()
{
    VkVertexInputBindingDescription BindingDescription{};

    BindingDescription.binding = 0u;
    BindingDescription.stride = sizeof(SNZ::Vertex);
    BindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return BindingDescription;
}

inline std::array<VkVertexInputAttributeDescription, 2u> SNZ::Vertex::GetAttributeDescriptions()
{
    std::array<VkVertexInputAttributeDescription, 2u> AttributeDescriptions{};

    AttributeDescriptions[0].binding = 0u;
    AttributeDescriptions[0].location = 0u;
    AttributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
    AttributeDescriptions[0].offset = offsetof(SNZ::Vertex, SNZ::Vertex::Position);

    AttributeDescriptions[1].binding = 0u;
    AttributeDescriptions[1].location = 1u;
    AttributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    AttributeDescriptions[1].offset = offsetof(SNZ::Vertex, SNZ::Vertex::Color);

    return AttributeDescriptions;
}

