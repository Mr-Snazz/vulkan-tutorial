#include <stdexcept>

#include "vulkan/helper-functions/begin-and-end-single-time-commands.hpp"
#include "vulkan/vulkan.hpp"

VkCommandBuffer SNZ::BegingSingleTimeCommands()
{
    VkCommandBufferAllocateInfo AllocateInfo{};
    AllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    AllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    AllocateInfo.commandPool = SNZ::CommandPool;
    AllocateInfo.commandBufferCount = 1u;
    
    VkCommandBuffer CommandBuffer;
    if (vkAllocateCommandBuffers(SNZ::LogicalDevice, &AllocateInfo, &CommandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("Failed to allocate command buffer");
    }

    VkCommandBufferBeginInfo BeginInfo{};
    BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    BeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    if (vkBeginCommandBuffer(CommandBuffer, &BeginInfo) != VK_SUCCESS) {
        throw std::runtime_error("Failed to begin command buffer");
    }

    return CommandBuffer;
}

void SNZ::EndSingleTimeCommands(VkCommandBuffer CommandBuffer)
{
    vkEndCommandBuffer(CommandBuffer);

    VkSubmitInfo SubmitInfo{};
    SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    SubmitInfo.commandBufferCount = 1u;
    SubmitInfo.pCommandBuffers = &CommandBuffer;

    vkQueueSubmit(SNZ::GraphicsQueue, 1u, &SubmitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(SNZ::GraphicsQueue);

    vkFreeCommandBuffers(SNZ::LogicalDevice, SNZ::CommandPool, 1u, &CommandBuffer);
}