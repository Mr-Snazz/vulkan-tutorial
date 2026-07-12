#include <stdexcept>
#include <array>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkan/helper-functions/create-framebuffers.hpp"
#include "vulkan/vulkan.hpp"
 
void SNZ::CreateFramebuffers()
{
    SNZ::SwapChainFramebuffers.resize(SNZ::SwapChainImageViews.size());

    for (size_t I{}; I < SNZ::SwapChainImageViews.size(); ++I) {
        std::array<VkImageView, 2u> Attachments = 
        {
            SNZ::SwapChainImageViews[I],
            SNZ::DepthImageView
        };
        
        VkFramebufferCreateInfo FramebufferInfo{};
        FramebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        FramebufferInfo.renderPass = SNZ::RenderPass;
        FramebufferInfo.attachmentCount = static_cast<uint32_t>(Attachments.size());
        FramebufferInfo.pAttachments = Attachments.data();
        FramebufferInfo.width = SNZ::SwapChainExtent.width;
        FramebufferInfo.height = SNZ::SwapChainExtent.height;
        FramebufferInfo.layers = 1u;

        if (vkCreateFramebuffer(SNZ::LogicalDevice, &FramebufferInfo, nullptr, &SNZ::SwapChainFramebuffers[I]) != VK_SUCCESS) throw std::runtime_error("Failed to create framebuffer");
    }
}