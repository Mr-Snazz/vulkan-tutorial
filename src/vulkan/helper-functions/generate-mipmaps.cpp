#include <stdexcept>

#include "vulkan/helper-functions/generate-mipmaps.hpp"
#include "vulkan/helper-functions/begin-and-end-single-time-commands.hpp"
#include "vulkan/vulkan.hpp"

void SNZ::GenerateMipmaps(VkImage Image, VkFormat ImageFormat,  int32_t Width, int32_t Height, uint32_t MipLevels)
{
    VkFormatProperties FormatProperties{};
    vkGetPhysicalDeviceFormatProperties(SNZ::PhysicalDevice, ImageFormat, &FormatProperties);

    if (!(FormatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)) throw std::runtime_error("Texture image format does not support linear blitting");

    VkCommandBuffer CommandBuffer = SNZ::BeginSingleTimeCommands();

    VkImageMemoryBarrier Barrier{};
    Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    Barrier.image = Image;
    Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    Barrier.subresourceRange.baseArrayLayer = 0u;
    Barrier.subresourceRange.layerCount = 1u;
    Barrier.subresourceRange.levelCount = 1u;

    int32_t MipWidth = Width;
    int32_t MipHeight = Height;

    for (uint32_t I = 1u; I < MipLevels; ++I) {
        Barrier.subresourceRange.baseMipLevel = I - 1;
        Barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        Barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
        Barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        Barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

        vkCmdPipelineBarrier
        (
            CommandBuffer,
            VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0u,
            0u, nullptr,
            0u, nullptr,
            1u, &Barrier
        );

        VkImageBlit Blit{};
        Blit.srcOffsets[0] = { 0, 0, 0 };
        Blit.srcOffsets[1] = { MipWidth, MipHeight, 1 };
        Blit.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        Blit.srcSubresource.mipLevel = I - 1;
        Blit.srcSubresource.baseArrayLayer = 0u;
        Blit.srcSubresource.layerCount = 1u;
        Blit.dstOffsets[0] = { 0, 0, 0 };
        Blit.dstOffsets[1] = { MipWidth > 1 ? MipWidth / 2 : 1, MipHeight > 1 ? MipHeight / 2 : 1, 1 };
        Blit.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        Blit.dstSubresource.mipLevel = I;
        Blit.dstSubresource.baseArrayLayer = 0u;
        Blit.dstSubresource.layerCount = 1u;

        vkCmdBlitImage
        (
            CommandBuffer,
            Image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
            Image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            1u, &Blit,
            VK_FILTER_LINEAR
        );  

        Barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
        Barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        Barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        vkCmdPipelineBarrier
        (
            CommandBuffer,
            VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0u,
            0u, nullptr,
            0u, nullptr,
            1u, &Barrier
        );

        if (MipWidth > 1) MipWidth /= 2;
        if (MipHeight > 1) MipHeight /= 2;
    }

    Barrier.subresourceRange.baseMipLevel = MipLevels - 1u;
    Barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    Barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    Barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

    vkCmdPipelineBarrier
    (
        CommandBuffer,
        VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0,
        0, nullptr,
        0, nullptr,
        1, &Barrier
    );

    SNZ::EndSingleTimeCommands(CommandBuffer);
}