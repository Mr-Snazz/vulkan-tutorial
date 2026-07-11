#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkan/helper-functions/cleanup-swap-chain.hpp"
#include "vulkan/vulkan.hpp"

void SNZ::CleanupSwapChain()
{
    for (const auto& Framebuffer : SNZ::SwapChainFramebuffers) {
        vkDestroyFramebuffer(SNZ::LogicalDevice, Framebuffer, nullptr);
    }

    for (const auto& ImageView : SNZ::SwapChainImageViews) {
        vkDestroyImageView(SNZ::LogicalDevice, ImageView, nullptr);
    } 

    vkDestroySwapchainKHR(SNZ::LogicalDevice, SNZ::SwapChain, nullptr);
}