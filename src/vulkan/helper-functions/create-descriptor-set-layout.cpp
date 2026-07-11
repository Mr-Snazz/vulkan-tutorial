#include <stdexcept>

#include <glm/glm.hpp>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkan/helper-functions/create-descriptor-set-layout.hpp"
#include "vulkan/vulkan.hpp"

void SNZ::CreateDescriptorSetLayout()
{
    VkDescriptorSetLayoutBinding UniformBufferObjectLayoutBinding{};
    UniformBufferObjectLayoutBinding.binding = 0u;
    UniformBufferObjectLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    UniformBufferObjectLayoutBinding.descriptorCount = 1u;
    UniformBufferObjectLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    UniformBufferObjectLayoutBinding.pImmutableSamplers = nullptr; // Optional

    VkDescriptorSetLayoutCreateInfo LayoutInfo{};
    LayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    LayoutInfo.bindingCount = 1u;
    LayoutInfo.pBindings = &UniformBufferObjectLayoutBinding;

    if (vkCreateDescriptorSetLayout(SNZ::LogicalDevice, &LayoutInfo, nullptr, &SNZ::DescriptorSetLayout) != VK_SUCCESS) throw std::runtime_error("Failed to create descriptor set layout");

    VkPipelineLayoutCreateInfo PipelineLayoutInfo{};
    PipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    PipelineLayoutInfo.setLayoutCount = 1u;
    PipelineLayoutInfo.pSetLayouts = &DescriptorSetLayout;
}

