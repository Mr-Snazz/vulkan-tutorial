#include <stdexcept>

#include "vulkan/helper-functions/create-image-view.hpp"
#include "vulkan/vulkan.hpp"

VkImageView SNZ::CreateImageView(VkImage Image, VkFormat Format, VkImageAspectFlags AspectFlags)
{
    VkImageViewCreateInfo ViewInfo{};
    ViewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    ViewInfo.image = Image;
    ViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    ViewInfo.format = Format;
    ViewInfo.subresourceRange.aspectMask = AspectFlags;
    ViewInfo.subresourceRange.baseMipLevel = 0u;
    ViewInfo.subresourceRange.levelCount = 1u;
    ViewInfo.subresourceRange.baseArrayLayer = 0u;
    ViewInfo.subresourceRange.layerCount = 1u;

    VkImageView ImageView{};
    if (vkCreateImageView(SNZ::LogicalDevice, &ViewInfo, nullptr, &ImageView) != VK_SUCCESS) throw std::runtime_error("Failed to create image view");

    return ImageView;
}