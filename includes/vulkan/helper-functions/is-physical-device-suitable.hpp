#pragma once

#include <vector>

#define GLFW_INCLUDE_VULKAN
#include "external/glfw3.h"

namespace SNZ
{
    bool IsPhysicalDeviceSuitable(const VkPhysicalDevice& Device, const std::vector<const char*>& DeviceExtensions);
}