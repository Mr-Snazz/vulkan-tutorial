#include <stdexcept>
#include <cstring>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkan/initialization-functions/create-vertex-buffer.hpp"
#include "vulkan/vulkan.hpp"
#include "vulkan/helper-functions/find-memory-type.hpp"
#include "vulkan/helper-functions/create-buffer.hpp"
#include "vulkan/helper-functions/copy-buffer.hpp"
 
void SNZ::CreateVertexBuffer()
{
    VkDeviceSize BufferSize = sizeof(SNZ::Vertices[0]) * SNZ::Vertices.size();


    VkBuffer StagingBuffer{};
    VkDeviceMemory StagingBufferMemory;
    SNZ::CreateBuffer
    (
        BufferSize, 
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        StagingBuffer, 
        StagingBufferMemory
    );

    void* Data{};
    vkMapMemory(SNZ::LogicalDevice, StagingBufferMemory, 0, BufferSize, 0, &Data);
    std::memcpy(Data, Vertices.data(), static_cast<size_t>(BufferSize));
    vkUnmapMemory(SNZ::LogicalDevice, StagingBufferMemory);

    SNZ::CreateBuffer
    (
        BufferSize, 
        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        SNZ::VertexBuffer, 
        SNZ::VertexBufferMemory
    );

    SNZ::CopyBuffer(StagingBuffer, VertexBuffer, BufferSize);

    vkDestroyBuffer(SNZ::LogicalDevice, StagingBuffer, nullptr);
    vkFreeMemory(SNZ::LogicalDevice, StagingBufferMemory, nullptr);
}