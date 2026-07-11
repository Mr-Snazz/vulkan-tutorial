#include <stdexcept>

#include "vulkan/helper-functions/create-descriptor-sets.hpp"
#include "vulkan/vulkan.hpp"
#include "vulkan/uniform-buffer-object.hpp"

void SNZ::CreateDescriptorSets()
{
    std::vector<VkDescriptorSetLayout> Layouts(SNZ::MaxFramesInFlight, SNZ::DescriptorSetLayout);
    VkDescriptorSetAllocateInfo AllocateInfo{};
    AllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    AllocateInfo.descriptorPool = SNZ::DescriptorPool;
    AllocateInfo.descriptorSetCount = static_cast<uint32_t>(SNZ::MaxFramesInFlight);
    AllocateInfo.pSetLayouts = Layouts.data();

    SNZ::DescriptorSets.resize(SNZ::MaxFramesInFlight);

    if (vkAllocateDescriptorSets(SNZ::LogicalDevice, &AllocateInfo, SNZ::DescriptorSets.data()) != VK_SUCCESS) throw std::runtime_error("Failed to allocate descriptor sets");

    for (uint8_t I{}; I < SNZ::MaxFramesInFlight; ++I) {
        VkDescriptorBufferInfo BufferInfo{};
        BufferInfo.buffer = SNZ::UniformBuffers[I];
        BufferInfo.offset = 0u;
        BufferInfo.range = sizeof(SNZ::UniformBufferObject);

        VkWriteDescriptorSet DescriptorWrite{};
        DescriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        DescriptorWrite.dstSet = SNZ::DescriptorSets[I];
        DescriptorWrite.dstBinding = 0u;
        DescriptorWrite.dstArrayElement = 0u;

        DescriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        DescriptorWrite.descriptorCount = 1u;

        DescriptorWrite.pBufferInfo = &BufferInfo;
        DescriptorWrite.pImageInfo = nullptr;
        DescriptorWrite.pTexelBufferView = nullptr;

        vkUpdateDescriptorSets(SNZ::LogicalDevice, 1u, &DescriptorWrite, 0u, nullptr);
        
    }
}