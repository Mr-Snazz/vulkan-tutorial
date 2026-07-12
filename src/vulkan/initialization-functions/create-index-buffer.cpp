#include <cstring>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkan/initialization-functions/create-index-buffer.hpp"
#include "vulkan/vulkan.hpp"
#include "vulkan/helper-functions/create-buffer.hpp"
#include "vulkan/helper-functions/copy-buffer.hpp"

void SNZ::CreateIndexBuffer()
{
    VkDeviceSize BufferSize = sizeof(SNZ::Indices[0]) * Indices.size();

    VkBuffer StagingBuffer{};
    VkDeviceMemory StagingBufferMemory{};
    SNZ::CreateBuffer
    (
        BufferSize,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        StagingBuffer,
        StagingBufferMemory  
    );

    void* Data{};
    vkMapMemory(SNZ::LogicalDevice, StagingBufferMemory, 0, BufferSize, 0, &Data);
    memcpy(Data, SNZ::Indices.data(), static_cast<size_t>(BufferSize));
    vkUnmapMemory(SNZ::LogicalDevice, StagingBufferMemory);

    SNZ::CreateBuffer
    (
        BufferSize, 
        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        SNZ::IndexBuffer, 
        SNZ::IndexBufferMemory
    );

    SNZ::CopyBuffer(StagingBuffer, SNZ::IndexBuffer, BufferSize);

    vkDestroyBuffer(SNZ::LogicalDevice, StagingBuffer, nullptr);
    vkFreeMemory(SNZ::LogicalDevice, StagingBufferMemory, nullptr);
}