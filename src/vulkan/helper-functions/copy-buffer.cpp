#include "vulkan/helper-functions/copy-buffer.hpp"
#include "vulkan/vulkan.hpp"
#include "vulkan/helper-functions/begin-and-end-single-time-commands.hpp"

void SNZ::CopyBuffer(VkBuffer SourceBuffer, VkBuffer DestinationBuffer, VkDeviceSize Size)
{
    VkCommandBuffer CommandBuffer = SNZ::BegingSingleTimeCommands();

    VkBufferCopy CopyRegion{};
    CopyRegion.srcOffset = 0;
    CopyRegion.dstOffset = 0;
    CopyRegion.size = Size;
    vkCmdCopyBuffer(CommandBuffer, SourceBuffer, DestinationBuffer, 1u, &CopyRegion);

    SNZ::EndSingleTimeCommands(CommandBuffer);
}