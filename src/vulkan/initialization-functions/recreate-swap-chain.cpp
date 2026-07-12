#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkan/initialization-functions/recreate-swap-chain.hpp"
#include "vulkan/vulkan.hpp"
#include "vulkan/initialization-functions/create-swapchain.hpp"
#include "vulkan/initialization-functions/create-image-views.hpp"
#include "vulkan/initialization-functions/create-framebuffers.hpp"
#include "glfw/glfw.hpp"
#include "vulkan/initialization-functions/cleanup-swap-chain.hpp"

#include <glm/glm.hpp>

void SNZ::RecreateSwapChain()
{
    int Width, Height;
    glfwGetFramebufferSize(SNZ::Window, &Width, &Height);
    while (!Width || !Height)
    {
        glfwGetFramebufferSize(SNZ::Window, &Width, &Height);
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(SNZ::LogicalDevice);

    SNZ::CleanupSwapChain();

    SNZ::CreateSwapchain();
    SNZ::CreateImageViews();
    SNZ::CreateFramebuffers();
}