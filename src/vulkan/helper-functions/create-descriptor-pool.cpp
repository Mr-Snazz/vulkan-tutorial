#include <stdexcept>

#include "vulkan/helper-functions/create-descriptor-pool.hpp"
#include "vulkan/vulkan.hpp"

void SNZ::CreateDescriptorPool()
{
    VkDescriptorPoolSize PoolSize{};
    PoolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    PoolSize.descriptorCount = static_cast<uint32_t>(SNZ::MaxFramesInFlight);

    VkDescriptorPoolCreateInfo PoolCreateInfo{};
    PoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    PoolCreateInfo.poolSizeCount = 1u;
    PoolCreateInfo.pPoolSizes = &PoolSize;
    PoolCreateInfo.maxSets = static_cast<uint32_t>(SNZ::MaxFramesInFlight);

    if (vkCreateDescriptorPool(SNZ::LogicalDevice, &PoolCreateInfo, nullptr, &DescriptorPool) != VK_SUCCESS) throw std::runtime_error("Failed to create descriptor pool");
}
