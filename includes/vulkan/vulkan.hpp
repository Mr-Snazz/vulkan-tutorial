#pragma once

#include <stdint.h>

#include <vector>

#define GLFW_INCLUDE_VULKAN
#include "external/glfw3.h"

namespace SNZ
{
    constexpr uint8_t MaxFramesInFlight = 2u;

    inline VkInstance VulkanInstance;

    inline VkPhysicalDevice PhysicalDevice;
    inline VkDevice LogicalDevice;

    inline VkQueue GraphicsQueue;
    inline VkQueue PresentQueue;

    inline VkSurfaceKHR Surface;

    inline VkSwapchainKHR SwapChain;
    inline std::vector<VkImage> SwapChainImages;
    inline VkFormat SwapChainImageFormat;
    inline VkExtent2D SwapChainExtent;
    inline std::vector<VkImageView> SwapChainImageViews;
    inline std::vector<VkFramebuffer> SwapChainFramebuffers;

    inline VkRenderPass RenderPass;
    inline VkPipelineLayout PipelineLayout;
    inline VkPipeline GraphicsPipeline;

    inline VkCommandPool CommandPool;

    inline std::vector<VkCommandBuffer> Commandbuffers;
    inline std::vector<VkSemaphore> ImageAvailableSemaphores;
    inline std::vector<VkSemaphore> RenderFinishedSemaphores;
    inline std::vector<VkFence> InFlightFences;

    void InitializeVulkan();

    void FreeVulkanResources();
}