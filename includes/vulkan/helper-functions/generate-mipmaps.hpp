#pragma once

#include <stdint.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace SNZ
{
    void GenerateMipmaps(VkImage Image, VkFormat ImageFormat, int32_t TextureWidth, int32_t TextureHeight, uint32_t MiplLevels);
}