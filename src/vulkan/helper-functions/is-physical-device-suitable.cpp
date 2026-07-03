#include "vulkan/helper-functions/is-physical-device-suitable.hpp"
#include "vulkan/helper-functions/find-queue-families.hpp"
#include "vulkan/helper-functions/check-device-extension-support.hpp"
#include "vulkan/helper-functions/swap-chain-support-details.hpp"
#include "vulkan/vulkan.hpp"

bool SNZ::IsPhysicalDeviceSuitable(const VkPhysicalDevice& Device, const std::vector<const char*>& DeviceExtensions)
{
    const SNZ::QueueFamilyIndices Indices = SNZ::FindQueueFamilies(Device);
    if (!Indices.IsComplete()) return false;

    bool ExtensionsSupported = SNZ::CheckDeviceExtensionSupport(Device, DeviceExtensions);
    if (!ExtensionsSupported) return false;

    bool SwapChainAdequate{};
    if (ExtensionsSupported) {
        SNZ::SwapChainSupportDetails SwapChainSupport = SNZ::QuerySwapChainSupport(Device);
        SwapChainAdequate = !SwapChainSupport.Formats.empty() && !SwapChainSupport.PresentModes.empty();
    }
    if (!SwapChainAdequate) return false;

    return true;
}