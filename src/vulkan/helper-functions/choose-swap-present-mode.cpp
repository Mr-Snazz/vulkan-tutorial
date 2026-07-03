#include "vulkan/helper-functions/choose-swap-present-mode.hpp"

VkPresentModeKHR SNZ::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& AvailablePresentModes)
{
    for (const auto& AvailablePresentMode : AvailablePresentModes) {
        if (AvailablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
            return AvailablePresentMode;
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR; // This mode is guaranteed to be available
}