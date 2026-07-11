#include <stdexcept>

#include "vulkan/helper-functions/transition-image-layout.hpp"
#include "vulkan/helper-functions/begin-and-end-single-time-commands.hpp"

void SNZ::TransitionImageLayout(VkImage Image, VkFormat Format, VkImageLayout OldLayout, VkImageLayout NewLayout)
{
    VkCommandBuffer CommandBuffer = SNZ::BegingSingleTimeCommands();

    VkImageMemoryBarrier Barrier{};
    Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    Barrier.oldLayout = OldLayout;
    Barrier.newLayout = NewLayout;

    Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

    Barrier.image = Image;
    Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    Barrier.subresourceRange.baseMipLevel = 0u;
    Barrier.subresourceRange.levelCount = 1u;
    Barrier.subresourceRange.baseArrayLayer = 0u;
    Barrier.subresourceRange.layerCount = 1u;

    Barrier.srcAccessMask = 0u; // TODO
    Barrier.dstAccessMask = 0u;

    VkPipelineStageFlags SourceStage{};
    VkPipelineStageFlags DestinationStage{};

    if (OldLayout == VK_IMAGE_LAYOUT_UNDEFINED && NewLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
        Barrier.srcAccessMask = 0u;
        Barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

        SourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        DestinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    } else if (OldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && NewLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
        Barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        SourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        DestinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    } else {
        throw std::runtime_error("Unsupported layout transition");
    }

    vkCmdPipelineBarrier
    (
        CommandBuffer,
        SourceStage, DestinationStage,
        0,
        0u, nullptr,
        0u, nullptr,
        1u, &Barrier
    );

    SNZ::EndSingleTimeCommands(CommandBuffer);
}