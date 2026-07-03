#include <vector>

#include "vulkan/helper-functions/find-queue-families.hpp"
#include "vulkan/vulkan.hpp"

SNZ::QueueFamilyIndices SNZ::FindQueueFamilies(const VkPhysicalDevice& Device)
{
    SNZ::QueueFamilyIndices Indices{};

    uint32_t QueueFamilyCount{};
    vkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> QueueFamilies(QueueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, QueueFamilies.data());

    for (uint32_t I{}; I < QueueFamilies.size(); ++I) {
        if (QueueFamilies[I].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            Indices.GraphicsFamily = I;
        }

        VkBool32 PresentSupport{};
        vkGetPhysicalDeviceSurfaceSupportKHR(Device, I, SNZ::Surface, &PresentSupport);

        if (PresentSupport) {
            Indices.PresentFamily = I;
        }

        if (Indices.IsComplete()) break;
    }

    return Indices;
}