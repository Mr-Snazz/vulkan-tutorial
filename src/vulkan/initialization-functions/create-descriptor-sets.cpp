#include <stdexcept>
#include <array>

#include "vulkan/initialization-functions/create-descriptor-sets.hpp"
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

        VkDescriptorImageInfo ImageInfo{};
        ImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        ImageInfo.imageView = SNZ::TextureImageView;
        ImageInfo.sampler = SNZ::TextureSampler;

        std::array<VkWriteDescriptorSet, 2> DescriptorWrites{};

        DescriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        DescriptorWrites[0].dstSet = SNZ::DescriptorSets[I];
        DescriptorWrites[0].dstBinding = 0u;
        DescriptorWrites[0].dstArrayElement = 0u;
        DescriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        DescriptorWrites[0].descriptorCount = 1u;
        DescriptorWrites[0].pBufferInfo = &BufferInfo;

        DescriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        DescriptorWrites[1].dstSet = SNZ::DescriptorSets[I];
        DescriptorWrites[1].dstBinding = 1u;
        DescriptorWrites[1].dstArrayElement = 0u;
        DescriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        DescriptorWrites[1].descriptorCount = 1u;
        DescriptorWrites[1].pImageInfo = &ImageInfo;

        vkUpdateDescriptorSets(SNZ::LogicalDevice, static_cast<uint32_t>(DescriptorWrites.size()), DescriptorWrites.data(), 0, nullptr);
        
    }
}