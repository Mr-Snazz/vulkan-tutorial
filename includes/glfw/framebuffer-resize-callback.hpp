#pragma once

#define GLFW_INCLUDE_VULKAN
#include "external/glfw3.h"

namespace SNZ
{
    void FramebufferResizeCallback(GLFWwindow* Window, int Width, int Height);
}