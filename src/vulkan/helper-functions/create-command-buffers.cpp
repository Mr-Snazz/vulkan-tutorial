#include <stdexcept>

#define GLFW_INCLUDE_VULKAN
#include "external/glfw3.h"

#include "vulkan/helper-functions/create-command-buffers.hpp"
#include "vulkan/vulkan.hpp"

void SNZ::CreateCommandBuffers()
{
    SNZ::Commandbuffers.resize(SNZ::MaxFramesInFlight);

    VkCommandBufferAllocateInfo AllocateInfo{};
    AllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    AllocateInfo.commandPool = SNZ::CommandPool;
    AllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    AllocateInfo.commandBufferCount = SNZ::Commandbuffers.size();

    if (vkAllocateCommandBuffers(SNZ::LogicalDevice, &AllocateInfo, SNZ::Commandbuffers.data()) != VK_SUCCESS) throw std::runtime_error("Failed to allocate command buffers");
}