#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkan/initialization-functions/create-swapchain.hpp"
#include "vulkan/queue-family-indices.hpp"
#include "vulkan/helper-functions/swap-chain-support-details.hpp"
#include "vulkan/vulkan.hpp"
#include "vulkan/helper-functions/choose-swap-surface-format.hpp"
#include "vulkan/helper-functions/choose-swap-present-mode.hpp"
#include "vulkan/helper-functions/choose-swap-extent.hpp"
#include "vulkan/helper-functions/find-queue-families.hpp"

void SNZ::CreateSwapchain()
{
    SwapChainSupportDetails SwapChainSupport = SNZ::QuerySwapChainSupport(SNZ::PhysicalDevice);

    VkSurfaceFormatKHR SurfaceFormat = SNZ::ChooseSwapSurfaceFormat(SwapChainSupport.Formats);
    VkPresentModeKHR PresentMode = SNZ::ChooseSwapPresentMode(SwapChainSupport.PresentModes);
    VkExtent2D Extent = SNZ::ChooseSwapExtent(SwapChainSupport.Capabilities);

    uint32_t ImageCount = SwapChainSupport.Capabilities.minImageCount + 1u;
    if (SwapChainSupport.Capabilities.maxImageCount > 0u && ImageCount > SwapChainSupport.Capabilities.maxImageCount) {
        ImageCount = SwapChainSupport.Capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR SwapChainCreateInfo{};
    SwapChainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    SwapChainCreateInfo.surface = SNZ::Surface;
    SwapChainCreateInfo.minImageCount = ImageCount;
    SwapChainCreateInfo.imageFormat = SurfaceFormat.format;
    SwapChainCreateInfo.imageColorSpace = SurfaceFormat.colorSpace;
    SwapChainCreateInfo.imageExtent = Extent;
    SwapChainCreateInfo.imageArrayLayers = 1u;
    SwapChainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    SNZ::QueueFamilyIndices QueueFamilyIndices = SNZ::FindQueueFamilies(SNZ::PhysicalDevice);
    uint32_t QueueFamilyIndicesArray[] = { QueueFamilyIndices.GraphicsFamily.value(), QueueFamilyIndices.PresentFamily.value() };

    if (QueueFamilyIndices.GraphicsFamily != QueueFamilyIndices.PresentFamily) {
        SwapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        SwapChainCreateInfo.queueFamilyIndexCount = 2u;
        SwapChainCreateInfo.pQueueFamilyIndices = QueueFamilyIndicesArray;
    } else {
        SwapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        SwapChainCreateInfo.queueFamilyIndexCount = 0u;
        SwapChainCreateInfo.pQueueFamilyIndices = nullptr;
    }
    SwapChainCreateInfo.preTransform = SwapChainSupport.Capabilities.currentTransform;
    SwapChainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    SwapChainCreateInfo.presentMode = PresentMode;
    SwapChainCreateInfo.clipped = VK_TRUE;
    SwapChainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

    if (vkCreateSwapchainKHR(SNZ::LogicalDevice, &SwapChainCreateInfo, nullptr, &SNZ::SwapChain) != VK_SUCCESS) {
        std::cerr << "Failed to create swap chain!\n";
        exit(EXIT_FAILURE);
    }
    vkGetSwapchainImagesKHR(SNZ::LogicalDevice, SNZ::SwapChain, &ImageCount, nullptr);
    SNZ::SwapChainImages.resize(ImageCount);
    vkGetSwapchainImagesKHR(SNZ::LogicalDevice, SNZ::SwapChain, &ImageCount, SNZ::SwapChainImages.data());

    SNZ::SwapChainImageFormat = SurfaceFormat.format;
    SNZ::SwapChainExtent = Extent;
}