#include <stdexcept>

#include "vulkan/helper-functions/record-command-buffer.hpp"
#include "vulkan/vulkan.hpp"

void SNZ::RecordCommandBuffer(VkCommandBuffer CommandBuffer, uint32_t ImageIndex)
{
    VkCommandBufferBeginInfo BeginInfo{};
    BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    BeginInfo.flags = 0u; // Optional
    BeginInfo.pInheritanceInfo = nullptr; // Optional

    if (vkBeginCommandBuffer(CommandBuffer, &BeginInfo) != VK_SUCCESS) throw std::runtime_error("Failed to begin recording command buffer");

    VkRenderPassBeginInfo RenderPassInfo{};
    RenderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    RenderPassInfo.renderPass = SNZ::RenderPass;
    RenderPassInfo.framebuffer = SNZ::SwapChainFramebuffers[ImageIndex];
    RenderPassInfo.renderArea.offset = {0, 0};
    RenderPassInfo.renderArea.extent = SNZ::SwapChainExtent;

    VkClearValue ClearColor = { { {0.0f, 0.0f, 0.0f, 1.0f } } };
    RenderPassInfo.clearValueCount = 1;
    RenderPassInfo.pClearValues = &ClearColor;

    vkCmdBeginRenderPass(CommandBuffer, &RenderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, SNZ::GraphicsPipeline);

    VkViewport Viewport{};
    Viewport.x = 0.0f;
    Viewport.y = 0.0f;
    Viewport.width = static_cast<float>(SNZ::SwapChainExtent.width);
    Viewport.height = static_cast<float>(SNZ::SwapChainExtent.height);
    Viewport.minDepth = 0.0f;
    Viewport.maxDepth = 1.0f;
    vkCmdSetViewport(CommandBuffer, 0, 1, &Viewport);

    VkRect2D Scissor{};
    Scissor.offset = {0, 0};
    Scissor.extent = SNZ::SwapChainExtent;
    vkCmdSetScissor(CommandBuffer, 0, 1, &Scissor);

    VkBuffer VertexBuffers[] = { SNZ::VertexBuffer };
    VkDeviceSize Offsets[] = { 0 };
    vkCmdBindVertexBuffers(CommandBuffer, 0u, 1u, VertexBuffers, Offsets);

    vkCmdDraw(CommandBuffer, static_cast<uint32_t>(SNZ::Vertices.size()), 1u, 0u, 0u);

    vkCmdEndRenderPass(CommandBuffer);

    if (vkEndCommandBuffer(CommandBuffer) != VK_SUCCESS) throw std::runtime_error("failed to record command buffer!");
}