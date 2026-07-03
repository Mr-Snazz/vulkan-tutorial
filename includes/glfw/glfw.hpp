#pragma once

#include <stdint.h>

#define GLFW_INCLUDE_VULKAN
#include "external/glfw3.h"

namespace SNZ
{
    constexpr uint32_t WindowWidth{ 800u };
    constexpr uint32_t WindowHeight{ 600u };

    inline GLFWwindow* Window{};

    void InitializeGLFW();

    void FreeGLFWResources();
}