#include "vulkan/helper-functions/choose-swap-surface-format.hpp"

VkSurfaceFormatKHR SNZ::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& AvailableFormats)
{
    for (const auto& AvailableFormat : AvailableFormats) {
        if (AvailableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && AvailableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return AvailableFormat;
        }
    }

    return AvailableFormats[0];
}