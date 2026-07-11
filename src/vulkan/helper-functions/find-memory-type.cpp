#include <stdexcept>

#include "vulkan/helper-functions/find-memory-type.hpp"
#include "vulkan/vulkan.hpp"

uint32_t SNZ::FindMemoryType(uint32_t TypeFilter, VkMemoryPropertyFlags Properties)
{
    VkPhysicalDeviceMemoryProperties MemoryProperties{};
    vkGetPhysicalDeviceMemoryProperties(SNZ::PhysicalDevice, &MemoryProperties);

    for (uint32_t I{}; I < MemoryProperties.memoryTypeCount; ++I) {
        if (!(TypeFilter & (1u << I))) continue;
        if ((MemoryProperties.memoryTypes[I].propertyFlags & Properties) != Properties) continue;

        return I;
    }

    throw std::runtime_error("Failed to find suitable memory type");
}

