#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include "external/glfw3.h"

#include "vulkan/helper-functions/create-image-views.hpp"
#include "vulkan/vulkan.hpp"

void SNZ::CreateImageViews()
{
    SNZ::SwapChainImageViews.resize(SNZ::SwapChainImages.size());
    for (size_t I{}; I < SNZ::SwapChainImages.size(); ++I) {
        VkImageViewCreateInfo ImageViewCreateInfo{};
        ImageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        ImageViewCreateInfo.image = SNZ::SwapChainImages[I];
        ImageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        ImageViewCreateInfo.format = SNZ::SwapChainImageFormat;
        ImageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        ImageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        ImageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        ImageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        ImageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        ImageViewCreateInfo.subresourceRange.baseMipLevel = 0u;
        ImageViewCreateInfo.subresourceRange.levelCount = 1u;
        ImageViewCreateInfo.subresourceRange.baseArrayLayer = 0u;
        ImageViewCreateInfo.subresourceRange.layerCount = 1u;

        if (vkCreateImageView(SNZ::LogicalDevice, &ImageViewCreateInfo, nullptr, &SNZ::SwapChainImageViews[I]) != VK_SUCCESS) {
            std::cerr << "Failed to create image views!\n";
            exit(EXIT_FAILURE);
        }
    }
}