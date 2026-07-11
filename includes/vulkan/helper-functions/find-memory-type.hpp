#pragma once

#include <stdint.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace SNZ
{
    uint32_t FindMemoryType(uint32_t TypeFilter, VkMemoryPropertyFlags Properties);
}