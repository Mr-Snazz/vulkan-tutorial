#include <algorithm>

#include "vulkan/helper-functions/choose-swap-extent.hpp"
#include "vulkan/vulkan.hpp"
#include "glfw/glfw.hpp"

VkExtent2D SNZ::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& Capabilities)
{
    if (Capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return Capabilities.currentExtent;
    } else {
        int Width, Height;
        glfwGetFramebufferSize(SNZ::Window, &Width, &Height);

        VkExtent2D ActualExtent = 
        {
            static_cast<uint32_t>(Width),
            static_cast<uint32_t>(Height)
        };

        ActualExtent.width = std::clamp(ActualExtent.width, Capabilities.minImageExtent.width, Capabilities.maxImageExtent.width);
        ActualExtent.height = std::clamp(ActualExtent.height, Capabilities.minImageExtent.height, Capabilities.maxImageExtent.height);

        return ActualExtent;
    }
} 

