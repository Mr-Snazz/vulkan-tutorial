#pragma once

#include <stdint.h>

#include <vector>

#include <glm/glm.hpp>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkan/vertex.hpp"

namespace SNZ
{
    inline const std::vector<SNZ::Vertex> Vertices = 
    {
        { {-0.5f, -0.5f,  0.0f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
        { { 0.5f, -0.5f,  0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } },
        { { 0.5f,  0.5f,  0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } },
        { {-0.5f,  0.5f,  0.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f } },

        { {-0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
        { { 0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } },
        { { 0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } },
        { {-0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f } }
    };

    inline const std::vector<uint16_t> Indices = 
    {
        0u, 1u, 2u,
        2u, 3u, 0u,

        4u, 5u, 6u,
        6u, 7u, 4u
    };

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

    inline VkImage DepthImage;
    inline VkDeviceMemory DepthImageMemory;
    inline VkImageView DepthImageView;

    inline VkRenderPass RenderPass;
    inline VkDescriptorSetLayout DescriptorSetLayout;
    inline VkPipelineLayout PipelineLayout;
    inline VkPipeline GraphicsPipeline;

    inline VkCommandPool CommandPool;

    inline std::vector<VkCommandBuffer> CommandBuffers;
    inline std::vector<VkSemaphore> ImageAvailableSemaphores;
    inline std::vector<VkSemaphore> RenderFinishedSemaphores;
    inline std::vector<VkFence> InFlightFences;

    inline VkBuffer VertexBuffer;
    inline VkDeviceMemory VertexBufferMemory;
    inline VkBuffer IndexBuffer;
    inline VkDeviceMemory IndexBufferMemory;

    inline std::vector<VkBuffer> UniformBuffers;
    inline std::vector<VkDeviceMemory> UniformBuffersMemory;
    inline std::vector<void*> UniformbuffersMapped;

    inline VkDescriptorPool DescriptorPool;
    inline std::vector<VkDescriptorSet> DescriptorSets;

    inline uint32_t MipLevels;
    inline VkImage TextureImage;
    inline VkDeviceMemory TextureImageMemory;
    inline VkImageView TextureImageView;
    inline VkSampler TextureSampler;

    inline bool FramebufferResized{};

    void InitializeVulkan();

    void FreeVulkanResources();
}