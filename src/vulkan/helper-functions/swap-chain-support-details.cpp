#include "vulkan/helper-functions/swap-chain-support-details.hpp"
#include "vulkan/vulkan.hpp"

SNZ::SwapChainSupportDetails SNZ::QuerySwapChainSupport(const VkPhysicalDevice& Device)
{
    SwapChainSupportDetails Details{};

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(Device, SNZ::Surface, &Details.Capabilities);

    uint32_t FormatCount{};
    vkGetPhysicalDeviceSurfaceFormatsKHR(Device, SNZ::Surface, &FormatCount, nullptr);

    if (FormatCount) {
        Details.Formats.resize(FormatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(Device, SNZ::Surface, &FormatCount, Details.Formats.data());
    }

    uint32_t PresentModeCount{};
    vkGetPhysicalDeviceSurfacePresentModesKHR(Device, SNZ::Surface, &PresentModeCount, nullptr);

    if (PresentModeCount) {
        Details.PresentModes.resize(PresentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(Device, SNZ::Surface, &PresentModeCount, Details.PresentModes.data());
    }

    return Details;
}