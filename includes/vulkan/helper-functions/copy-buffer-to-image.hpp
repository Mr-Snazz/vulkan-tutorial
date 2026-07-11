#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace SNZ
{
    void CopyBufferToImage(VkBuffer Buffer, VkImage Image, uint32_t Width, uint32_t Height);
}