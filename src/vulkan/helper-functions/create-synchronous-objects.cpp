#include <stdexcept>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkan/helper-functions/create-synchronous-objects.hpp"
#include "vulkan/vulkan.hpp"

void SNZ::CreateSynchronousObjects()
{
    SNZ::ImageAvailableSemaphores.resize(SNZ::MaxFramesInFlight);
    SNZ::RenderFinishedSemaphores.resize(SNZ::MaxFramesInFlight);
    SNZ::InFlightFences.resize(SNZ::MaxFramesInFlight);

    VkSemaphoreCreateInfo SemaphoreCreateInfo{};
    SemaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo FenceCreateInfo{};
    FenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    FenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (uint8_t I{}; I < SNZ::MaxFramesInFlight; ++I) {
        if 
        (
            vkCreateSemaphore(SNZ::LogicalDevice, &SemaphoreCreateInfo, nullptr, &SNZ::ImageAvailableSemaphores[I]) != VK_SUCCESS ||
            vkCreateSemaphore(SNZ::LogicalDevice, &SemaphoreCreateInfo, nullptr, &SNZ::RenderFinishedSemaphores[I]) != VK_SUCCESS ||
            vkCreateFence    (SNZ::LogicalDevice, &FenceCreateInfo,     nullptr, &SNZ::InFlightFences[I]          ) != VK_SUCCESS
        ) 
        {
            throw std::runtime_error("Failed to create semaphore");
        }
    }
}