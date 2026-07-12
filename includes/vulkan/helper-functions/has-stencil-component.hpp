#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace SNZ
{
    inline bool HasStencilComponent(VkFormat Format);
}

#include "vulkan/helper-functions/has-stencil-format.inl"
