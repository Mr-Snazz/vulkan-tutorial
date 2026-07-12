#include <stdexcept>

#include <glm/glm.hpp>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkan/helper-functions/create-descriptor-set-layout.hpp"
#include "vulkan/vulkan.hpp"
#include "vulkan/vulkan.hpp"

void SNZ::CreateDescriptorSetLayout()
{
    VkDescriptorSetLayoutBinding UniformBufferObjectLayoutBinding{};
    UniformBufferObjectLayoutBinding.binding = 0u;
    UniformBufferObjectLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    UniformBufferObjectLayoutBinding.descriptorCount = 1u;
    UniformBufferObjectLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    UniformBufferObjectLayoutBinding.pImmutableSamplers = nullptr; // Optional

    VkDescriptorSetLayoutBinding SamplerLayoutBinding{};
    SamplerLayoutBinding.binding = 1;
    SamplerLayoutBinding.descriptorCount = 1;
    SamplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    SamplerLayoutBinding.pImmutableSamplers = nullptr;
    SamplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

    std::array<VkDescriptorSetLayoutBinding, 2> Bindings = { UniformBufferObjectLayoutBinding, SamplerLayoutBinding };
    VkDescriptorSetLayoutCreateInfo LayoutInfo{};
    LayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    LayoutInfo.bindingCount = static_cast<uint32_t>(Bindings.size());
    LayoutInfo.pBindings = Bindings.data();

    if (vkCreateDescriptorSetLayout(SNZ::LogicalDevice, &LayoutInfo, nullptr, &SNZ::DescriptorSetLayout) != VK_SUCCESS) throw std::runtime_error("Failed to create descriptor set layout");
}

