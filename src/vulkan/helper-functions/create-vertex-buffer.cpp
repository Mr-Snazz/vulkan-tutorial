#include <stdexcept>
#include <cstring>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkan/helper-functions/create-vertex-buffer.hpp"
#include "vulkan/vulkan.hpp"
#include "vulkan/helper-functions/find-memory-type.hpp"
 
void SNZ::CreateVertexBuffer()
{
    VkBufferCreateInfo BufferInfo{};
    BufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    BufferInfo.size = sizeof(SNZ::Vertices[0]) * SNZ::Vertices.size();
    BufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    BufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(SNZ::LogicalDevice, &BufferInfo, nullptr, &SNZ::VertexBuffer) != VK_SUCCESS) throw std::runtime_error("Failed to create vertex buffer");

    VkMemoryRequirements MemoryRequirements{};
    vkGetBufferMemoryRequirements(SNZ::LogicalDevice, SNZ::VertexBuffer, &MemoryRequirements);

    VkMemoryAllocateInfo AllocationInfo{};
    AllocationInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    AllocationInfo.allocationSize = MemoryRequirements.size;
    AllocationInfo.memoryTypeIndex = SNZ::FindMemoryType(MemoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    if (vkAllocateMemory(SNZ::LogicalDevice, &AllocationInfo, nullptr, &SNZ::VertexBufferMemory) != VK_SUCCESS) throw std::runtime_error("Failed to allocate vertex buffer memory");

    vkBindBufferMemory(SNZ::LogicalDevice, SNZ::VertexBuffer, SNZ::VertexBufferMemory, 0);

    void* Data{};
    vkMapMemory(SNZ::LogicalDevice, SNZ::VertexBufferMemory, 0, BufferInfo.size, 0, &Data);
    std::memcpy(Data, SNZ::Vertices.data(), static_cast<size_t>(BufferInfo.size));
    vkUnmapMemory(SNZ::LogicalDevice, SNZ::VertexBufferMemory);
}