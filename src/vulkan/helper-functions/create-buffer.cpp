#include <stdexcept>

#include "vulkan/helper-functions/create-buffer.hpp"
#include "vulkan/vulkan.hpp"
#include "vulkan/helper-functions/find-memory-type.hpp"
#include "vulkan/helper-functions/copy-buffer.hpp"

void SNZ::CreateBuffer(VkDeviceSize Size, VkBufferUsageFlags Usage, VkMemoryPropertyFlags Properties, VkBuffer& Buffer, VkDeviceMemory& BufferMemory)
{
    VkBufferCreateInfo BufferInfo{};
    BufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    BufferInfo.size = Size;
    BufferInfo.usage = Usage;
    BufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(SNZ::LogicalDevice, &BufferInfo, nullptr, &Buffer) != VK_SUCCESS) throw std::runtime_error("Failed to create buffer");

    VkMemoryRequirements MemoryRequirements;
    vkGetBufferMemoryRequirements(SNZ::LogicalDevice, Buffer, &MemoryRequirements);

    VkMemoryAllocateInfo AllocateInfo{};
    AllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    AllocateInfo.allocationSize = MemoryRequirements.size;
    AllocateInfo.memoryTypeIndex = SNZ::FindMemoryType(MemoryRequirements.memoryTypeBits, Properties);

    if (vkAllocateMemory(SNZ::LogicalDevice, &AllocateInfo, nullptr, &BufferMemory) != VK_SUCCESS) throw std::runtime_error("Failed to allocate buffer memory");

    vkBindBufferMemory(SNZ::LogicalDevice, Buffer, BufferMemory, 0);
}