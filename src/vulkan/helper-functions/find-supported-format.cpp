#include <stdexcept>

#include "vulkan/helper-functions/find-supported-format.hpp"
#include "vulkan/vulkan.hpp"

VkFormat SNZ::FindSupportedFormat(const std::vector<VkFormat>& Candidates, VkImageTiling Tiliing, VkFormatFeatureFlags Features)
{
    for (VkFormat Format : Candidates) {
        VkFormatProperties Properties{};
        vkGetPhysicalDeviceFormatProperties(SNZ::PhysicalDevice, Format, &Properties);

        if (Tiliing == VK_IMAGE_TILING_LINEAR && (Properties.linearTilingFeatures & Features) == Features) {
            return Format;
        } else if (Tiliing == VK_IMAGE_TILING_OPTIMAL && (Properties.optimalTilingFeatures & Features) == Features) {
            return Format;
        }
    }

    throw std::runtime_error("Failed to find supported format");
}