#include <stdint.h>

#include <iostream>
#include <vector>
#include <cstring>

#include "core/core.hpp"
#include "glfw/glfw.hpp"
#include "vulkan/vulkan.hpp"
#include "vulkan/helper-functions/record-command-buffer.hpp"
#include "vulkan/helper-functions/recreate-swap-chain.hpp"
#include "vulkan/helper-functions/update-uniform-buffer.hpp"

void SNZ::Initialize()
{
    SNZ::InitializeGLFW();
    SNZ::InitializeVulkan();
}

void SNZ::MainLoop()
{
    uint32_t CurrentFrame{};

    while (!glfwWindowShouldClose(Window))
    {
        glfwPollEvents();

        // Draw frame
        vkWaitForFences(SNZ::LogicalDevice, 1u, &InFlightFences[CurrentFrame], VK_TRUE, UINT64_MAX);
        vkResetFences(SNZ::LogicalDevice, 1u, &SNZ::InFlightFences[CurrentFrame]);

        uint32_t ImageIndex{};
        VkResult Result = vkAcquireNextImageKHR(SNZ::LogicalDevice, SNZ::SwapChain, UINT64_MAX, SNZ::ImageAvailableSemaphores[CurrentFrame], VK_NULL_HANDLE, &ImageIndex);

        if (Result == VK_ERROR_OUT_OF_DATE_KHR || Result == VK_SUBOPTIMAL_KHR || SNZ::FramebufferResized) {
            SNZ::FramebufferResized = false;
            SNZ::RecreateSwapChain();
            continue;
        } else if (Result != VK_SUCCESS && Result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("Failed to aquire swap chain image");
        }

        vkResetFences(SNZ::LogicalDevice, 1u, &SNZ::InFlightFences[CurrentFrame]);

        SNZ::UpdateUniformBuffer(CurrentFrame);

        vkResetCommandBuffer(SNZ::Commandbuffers[CurrentFrame], 0);
        SNZ::RecordCommandBuffer(SNZ::Commandbuffers[CurrentFrame], ImageIndex, CurrentFrame);

        VkSubmitInfo SubmitInfo{};
        SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore WaitSemaphores[] = { SNZ::ImageAvailableSemaphores[CurrentFrame] };
        VkPipelineStageFlags WaitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

        SubmitInfo.waitSemaphoreCount = 1u;
        SubmitInfo.pWaitSemaphores = WaitSemaphores;
        SubmitInfo.pWaitDstStageMask = WaitStages;

        VkSemaphore SignalSemaphores[] = { SNZ::RenderFinishedSemaphores[CurrentFrame] };
        SubmitInfo.signalSemaphoreCount = 1u;
        SubmitInfo.pSignalSemaphores = SignalSemaphores;
        SubmitInfo.commandBufferCount = 1u;
        SubmitInfo.pCommandBuffers = &SNZ::Commandbuffers[CurrentFrame];

        if (vkQueueSubmit(SNZ::GraphicsQueue, 1u, &SubmitInfo, SNZ::InFlightFences[CurrentFrame]) != VK_SUCCESS) throw std::runtime_error("Failed to submit draw command buffer!");

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

        CurrentFrame = (CurrentFrame + 1u) % SNZ::MaxFramesInFlight;
    }

    vkDeviceWaitIdle(SNZ::LogicalDevice);
}

void SNZ::FreeResources()
{
    SNZ::FreeVulkanResources();
    SNZ::FreeGLFWResources();
}