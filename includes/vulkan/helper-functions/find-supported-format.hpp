#pragma once

#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace SNZ
{
    VkFormat FindSupportedFormat(const std::vector<VkFormat>& Candidates, VkImageTiling Tiliing, VkFormatFeatureFlags Features);
}