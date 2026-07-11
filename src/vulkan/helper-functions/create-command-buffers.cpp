#include <stdexcept>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkan/helper-functions/create-command-buffers.hpp"
#include "vulkan/vulkan.hpp"

void SNZ::CreateCommandBuffers()
{
    SNZ::CommandBuffers.resize(SNZ::MaxFramesInFlight);

    VkCommandBufferAllocateInfo AllocateInfo{};
    AllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    AllocateInfo.commandPool = SNZ::CommandPool;
    AllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    AllocateInfo.commandBufferCount = SNZ::CommandBuffers.size();

    if (vkAllocateCommandBuffers(SNZ::LogicalDevice, &AllocateInfo, SNZ::CommandBuffers.data()) != VK_SUCCESS) throw std::runtime_error("Failed to allocate command buffers");
}