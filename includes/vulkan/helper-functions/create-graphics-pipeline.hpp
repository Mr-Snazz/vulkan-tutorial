#pragma once

#define GLFW_INCLUDE_VULKAN
#include "external/glfw3.h"

namespace SNZ
{
    void CreateGraphicsPipeline(const VkDevice& LogicalDevice);
}