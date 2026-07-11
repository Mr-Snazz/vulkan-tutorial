#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace SNZ
{
    void CopyBuffer(VkBuffer SourceBuffer, VkBuffer DestinationBuffer, VkDeviceSize Size);
}