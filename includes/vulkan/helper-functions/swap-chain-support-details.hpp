#pragma once

#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace SNZ
{
    class SwapChainSupportDetails
    {
    public:
        VkSurfaceCapabilitiesKHR Capabilities{};
        std::vector<VkSurfaceFormatKHR> Formats;
        std::vector<VkPresentModeKHR> PresentModes;

    private:

    };

    SNZ::SwapChainSupportDetails QuerySwapChainSupport(const VkPhysicalDevice& Device);
}