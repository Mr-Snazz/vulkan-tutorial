#include <stdexcept>

#define GLFW_INCLUDE_VULKAN
#include "external/glfw3.h"

#include "vulkan/helper-functions/create-command-buffer.hpp"
#include "vulkan/vulkan.hpp"

void SNZ::CreateCommandBuffer()
{
    VkCommandBufferAllocateInfo AllocateInfo{};
    AllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    AllocateInfo.commandPool = SNZ::CommandPool;
    AllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    AllocateInfo.commandBufferCount = 1u;

    if (vkAllocateCommandBuffers(SNZ::LogicalDevice, &AllocateInfo, &Commandbuffer) != VK_SUCCESS) throw std::runtime_error("Failed to allocate command buffers");
}