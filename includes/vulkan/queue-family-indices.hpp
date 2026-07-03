#pragma once

#include <stdint.h>

#include <optional>

#define GLFW_INCLUDE_VULKAN
#include "external/glfw3.h"

namespace SNZ
{
    class QueueFamilyIndices
    {
    public:
        std::optional<uint32_t> GraphicsFamily;
        std::optional<uint32_t> PresentFamily;

        inline bool IsComplete() const;

    private:


    };  
}

#include "vulkan/queue-family-indices.inl"