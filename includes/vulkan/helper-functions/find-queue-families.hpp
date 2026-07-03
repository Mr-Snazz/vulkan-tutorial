#pragma once

#define GLFW_INCLUDE_VULKAN
#include "external/glfw3.h"

#include "vulkan/queue-family-indices.hpp"

namespace SNZ
{
    SNZ::QueueFamilyIndices FindQueueFamilies(const VkPhysicalDevice& Device);
}