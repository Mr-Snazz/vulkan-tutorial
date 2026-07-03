#include <stdexcept>

#define GLFW_INCLUDE_VULKAN
#include "external/glfw3.h"

#include "vulkan/helper-functions/create-synchronous-objects.hpp"
#include "vulkan/vulkan.hpp"

void SNZ::CreateSynchronousObjects()
{
    VkSemaphoreCreateInfo SemaphoreCreateInfo{};
    SemaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo FenceCreateInfo{};
    FenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    FenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    if 
    (
        vkCreateSemaphore(SNZ::LogicalDevice, &SemaphoreCreateInfo, nullptr, &SNZ::ImageAvailableSemaphore) != VK_SUCCESS ||
        vkCreateSemaphore(SNZ::LogicalDevice, &SemaphoreCreateInfo, nullptr, &SNZ::RenderFinishedSemaphore) != VK_SUCCESS ||
        vkCreateFence    (SNZ::LogicalDevice, &FenceCreateInfo,     nullptr, &SNZ::InFlightFence          ) != VK_SUCCESS
    ) 
    {
        throw std::runtime_error("failed to create semaphores!");
    }
}