#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace SNZ
{
    VkImageView CreateImageView(VkImage Image, VkFormat Format, VkImageAspectFlags AspectFlags, uint32_t MipLevels);
}