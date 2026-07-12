#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkan/initialization-functions/create-image-views.hpp"
#include "vulkan/vulkan.hpp"
#include "vulkan/helper-functions/create-image-view.hpp"

void SNZ::CreateImageViews()
{
    SNZ::SwapChainImageViews.resize(SNZ::SwapChainImages.size());

    for (size_t I{}; I < SNZ::SwapChainImages.size(); ++I) {
        SNZ::SwapChainImageViews[I] = SNZ::CreateImageView(SNZ::SwapChainImages[I], SNZ::SwapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT, SNZ::MipLevels);
    }
}