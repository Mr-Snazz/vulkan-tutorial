#include <stdexcept>
#include <array>

#include "vulkan/helper-functions/create-descriptor-pool.hpp"
#include "vulkan/vulkan.hpp"

void SNZ::CreateDescriptorPool()
{
    std::array<VkDescriptorPoolSize, 2> PoolSizes{};
    PoolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    PoolSizes[0].descriptorCount = static_cast<uint32_t>(SNZ::MaxFramesInFlight);
    PoolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    PoolSizes[1].descriptorCount = static_cast<uint32_t>(SNZ::MaxFramesInFlight);
    
    VkDescriptorPoolCreateInfo PoolInfo{};
    PoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    PoolInfo.poolSizeCount = static_cast<uint32_t>(PoolSizes.size());
    PoolInfo.pPoolSizes = PoolSizes.data();
    PoolInfo.maxSets = static_cast<uint32_t>(SNZ::MaxFramesInFlight);

    if (vkCreateDescriptorPool(SNZ::LogicalDevice, &PoolInfo, nullptr, &DescriptorPool) != VK_SUCCESS) throw std::runtime_error("Failed to create descriptor pool");
}
