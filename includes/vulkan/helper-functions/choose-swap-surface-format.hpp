#pragma once

#include <vector>

#define GLFW_INCLUDE_VULKAN
#include "external/glfw3.h"

namespace SNZ
{
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& AvailableFormats);
}