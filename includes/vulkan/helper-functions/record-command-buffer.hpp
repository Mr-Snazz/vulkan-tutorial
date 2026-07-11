#pragma once

#include <stdint.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace SNZ
{
    void RecordCommandBuffer(VkCommandBuffer CommandBuffer, uint32_t ImageIndex, uint32_t FrameIndex);
}