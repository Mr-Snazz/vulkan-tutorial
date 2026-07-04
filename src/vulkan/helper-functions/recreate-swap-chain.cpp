#define GLFW_INCLUDE_VULKAN
#include "external/glfw3.h"

#include "vulkan/helper-functions/recreate-swap-chain.hpp"
#include "vulkan/vulkan.hpp"
#include "vulkan/helper-functions/create-swapchain.hpp"
#include "vulkan/helper-functions/create-image-views.hpp"
#include "vulkan/helper-functions/create-framebuffers.hpp"
#include "glfw/glfw.hpp"

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

    SNZ::CreateSwapchain();
    SNZ::CreateImageViews();
    SNZ::CreateFramebuffers();
}