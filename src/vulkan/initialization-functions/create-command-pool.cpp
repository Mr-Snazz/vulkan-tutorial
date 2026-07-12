#include <stdexcept>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkan/initialization-functions/create-command-pool.hpp"
#include "vulkan/vulkan.hpp"
#include "vulkan/queue-family-indices.hpp"
#include "vulkan/helper-functions/find-queue-families.hpp"

void SNZ::CreateCommandPool()
{   
    SNZ::QueueFamilyIndices QueueFamilyIndices = SNZ::FindQueueFamilies(SNZ::PhysicalDevice);

    VkCommandPoolCreateInfo CommandPoolCreateInfo{};
    CommandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    CommandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    CommandPoolCreateInfo.queueFamilyIndex = QueueFamilyIndices.GraphicsFamily.value();

    if (vkCreateCommandPool(SNZ::LogicalDevice, &CommandPoolCreateInfo, nullptr, &SNZ::CommandPool) != VK_SUCCESS) throw std::runtime_error("Failed to create command pool!");
}