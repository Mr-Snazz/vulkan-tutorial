#include <stdexcept>

#include "vulkan/helper-functions/transition-image-layout.hpp"
#include "vulkan/helper-functions/begin-and-end-single-time-commands.hpp"
#include "vulkan/vulkan.hpp"

void SNZ::TransitionImageLayout(VkImage Image, VkFormat Format, VkImageLayout OldLayout, VkImageLayout NewLayout, uint32_t MipLevels)
{
    VkCommandBuffer CommandBuffer = SNZ::BeginSingleTimeCommands();

    VkImageMemoryBarrier Barrier{};
    Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    Barrier.oldLayout = OldLayout;
    Barrier.newLayout = NewLayout;

    Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

    Barrier.image = Image;
    Barrier.subresourceRange.aspectMask = (Format == VK_FORMAT_D32_SFLOAT) ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT;
    Barrier.subresourceRange.baseMipLevel = 0u;
    Barrier.subresourceRange.levelCount = MipLevels;
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
    } else if (OldLayout == VK_IMAGE_LAYOUT_UNDEFINED && NewLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
        Barrier.srcAccessMask = 0u;
        Barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

        SourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        DestinationStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
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