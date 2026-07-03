#include <stdint.h>

#include <iostream>
#include <vector>
#include <cstring>

#include "core/core.hpp"
#include "glfw/glfw.hpp"
#include "vulkan/vulkan.hpp"
#include "vulkan/helper-functions/record-command-buffer.hpp"

void SNZ::Initialize()
{
    SNZ::InitializeGLFW();
    SNZ::InitializeVulkan();
}

void SNZ::MainLoop()
{
    while (!glfwWindowShouldClose(Window))
    {
        glfwPollEvents();

        // Draw frame
        vkWaitForFences(SNZ::LogicalDevice, 1u, &InFlightFence, VK_TRUE, UINT64_MAX);
        vkResetFences(SNZ::LogicalDevice, 1u, &SNZ::InFlightFence);

        uint32_t ImageIndex{};
        vkAcquireNextImageKHR(SNZ::LogicalDevice, SNZ::SwapChain, UINT64_MAX, SNZ::ImageAvailableSemaphore, VK_NULL_HANDLE, &ImageIndex);

        vkResetCommandBuffer(SNZ::Commandbuffer, 0);
        SNZ::RecordCommandBuffer(SNZ::Commandbuffer, ImageIndex);

        VkSubmitInfo SubmitInfo{};
        SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore WaitSemaphores[] = { SNZ::ImageAvailableSemaphore };
        VkPipelineStageFlags WaitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

        SubmitInfo.waitSemaphoreCount = 1u;
        SubmitInfo.pWaitSemaphores = WaitSemaphores;
        SubmitInfo.pWaitDstStageMask = WaitStages;

        VkSemaphore SignalSemaphores[] = { SNZ::RenderFinishedSemaphore };
        SubmitInfo.signalSemaphoreCount = 1u;
        SubmitInfo.pSignalSemaphores = SignalSemaphores;
        SubmitInfo.commandBufferCount = 1u;
        SubmitInfo.pCommandBuffers = &SNZ::Commandbuffer;

        if (vkQueueSubmit(SNZ::GraphicsQueue, 1, &SubmitInfo, SNZ::InFlightFence) != VK_SUCCESS) throw std::runtime_error("Failed to submit draw command buffer!");

        VkPresentInfoKHR PresentInfo{};
        PresentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        PresentInfo.waitSemaphoreCount = 1u;
        PresentInfo.pWaitSemaphores = SignalSemaphores;

        VkSwapchainKHR Swapchains[] = 
        {
            SNZ::SwapChain
        };
        PresentInfo.swapchainCount = 1u;
        PresentInfo.pSwapchains = Swapchains;
        PresentInfo.pImageIndices = &ImageIndex;
        PresentInfo.pResults = nullptr;

        vkQueuePresentKHR(PresentQueue, &PresentInfo);

    }

    vkDeviceWaitIdle(SNZ::LogicalDevice);
}

void SNZ::FreeResources()
{
    SNZ::FreeVulkanResources();
    SNZ::FreeGLFWResources();
}