#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkan/helper-functions/create-uniform-buffers.hpp"
#include "vulkan/uniform-buffer-object.hpp"
#include "vulkan/vulkan.hpp"
#include "vulkan/helper-functions/create-buffer.hpp"

void SNZ::CreateUniformBuffers()
{
    VkDeviceSize BufferSize = sizeof(SNZ::UniformBufferObject);

    SNZ::UniformBuffers.resize(SNZ::MaxFramesInFlight);
    SNZ::UniformBuffersMemory.resize(SNZ::MaxFramesInFlight);
    SNZ::UniformbuffersMapped.resize(SNZ::MaxFramesInFlight);

    for (uint8_t I{}; I < SNZ::MaxFramesInFlight; ++I) {
        SNZ::CreateBuffer
        (
            BufferSize,
            VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            SNZ::UniformBuffers[I],
            SNZ::UniformBuffersMemory[I]
        );

        vkMapMemory(SNZ::LogicalDevice, SNZ::UniformBuffersMemory[I], 0, BufferSize, 0, &UniformbuffersMapped[I]);
    }
}