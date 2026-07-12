#pragma once

#include <stdint.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace SNZ
{
    void CreateImage(uint32_t Width, uint32_t Height, uint32_t MipLevels, VkFormat Format, VkImageTiling Tiling, VkImageUsageFlags Usage, VkMemoryPropertyFlags Properties, VkImage& Image, VkDeviceMemory& ImageMemory);
}