#pragma once

#define GLFW_INCLUDE_VULKAN
#include "external/glfw3.h"

namespace SNZ
{
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& Capabilities);
}