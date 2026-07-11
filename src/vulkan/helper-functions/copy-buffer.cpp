#include "vulkan/helper-functions/copy-buffer.hpp"
#include "vulkan/vulkan.hpp"

void SNZ::CopyBuffer(VkBuffer SourceBuffer, VkBuffer DestinationBuffer, VkDeviceSize Size)
{
    VkCommandBufferAllocateInfo AllocateInfo{};
    AllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    AllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    AllocateInfo.commandPool = SNZ::CommandPool;
    AllocateInfo.commandBufferCount = 1u;

    VkCommandBuffer CommandBuffer{};
    vkAllocateCommandBuffers(SNZ::LogicalDevice, &AllocateInfo, &CommandBuffer);

    VkCommandBufferBeginInfo BeginInfo{};
    BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    BeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(CommandBuffer, &BeginInfo);

    VkBufferCopy CopyRegion{};
    CopyRegion.srcOffset = 0;
    CopyRegion.dstOffset = 0;
    CopyRegion.size = Size;
    vkCmdCopyBuffer(CommandBuffer, SourceBuffer, DestinationBuffer, 1u, &CopyRegion);

    vkEndCommandBuffer(CommandBuffer);

    VkSubmitInfo SubmitInfo{};
    SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    SubmitInfo.commandBufferCount = 1u;
    SubmitInfo.pCommandBuffers = &CommandBuffer;

    vkQueueSubmit(SNZ::GraphicsQueue, 1u, &SubmitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(SNZ::GraphicsQueue);

    vkFreeCommandBuffers(SNZ::LogicalDevice, CommandPool, 1u, &CommandBuffer);
}