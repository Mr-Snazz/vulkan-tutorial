#include "vulkan/initialization-functions/copy-buffer-to-image.hpp"
#include "vulkan/helper-functions/begin-and-end-single-time-commands.hpp"

void SNZ::CopyBufferToImage(VkBuffer Buffer, VkImage Image, uint32_t Width, uint32_t Height)
{
    VkCommandBuffer CommandBuffer = SNZ::BeginSingleTimeCommands();

    VkBufferImageCopy Region{};
    Region.bufferOffset = 0;
    Region.bufferRowLength = 0u;
    Region.bufferImageHeight = 0u;

    Region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    Region.imageSubresource.mipLevel = 0u;
    Region.imageSubresource.baseArrayLayer = 0u;
    Region.imageSubresource.layerCount = 1u;

    Region.imageOffset = 
    { 
        0u, 
        0u, 
        0u 
    };
    Region.imageExtent = 
    {
        Width,
        Height,
        1u
    };

    vkCmdCopyBufferToImage
    (
        CommandBuffer,
        Buffer,
        Image,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        1u,
        &Region
    );

    SNZ::EndSingleTimeCommands(CommandBuffer);
}