#include <stdexcept>

#include "vulkan/helper-functions/create-image.hpp"
#include "vulkan/vulkan.hpp"
#include "vulkan/helper-functions/find-memory-type.hpp"

void SNZ::CreateImage(uint32_t Width, uint32_t Height, uint32_t MipLevels, VkFormat Format, VkImageTiling Tiling, VkImageUsageFlags Usage, VkMemoryPropertyFlags Properties, VkImage& Image, VkDeviceMemory& ImageMemory)
{
    VkImageCreateInfo ImageInfo{};
    ImageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    ImageInfo.imageType = VK_IMAGE_TYPE_2D;
    ImageInfo.extent.width = Width;
    ImageInfo.extent.height = Height;
    ImageInfo.extent.depth = 1u;
    ImageInfo.mipLevels = MipLevels;
    ImageInfo.arrayLayers = 1u;
    ImageInfo.format = Format;
    ImageInfo.tiling = Tiling;
    ImageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    ImageInfo.usage = Usage;
    ImageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    ImageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateImage(SNZ::LogicalDevice, &ImageInfo, nullptr, &Image) != VK_SUCCESS) throw std::runtime_error("Failed to create image");

    VkMemoryRequirements MemoryRequirements{};
    vkGetImageMemoryRequirements(SNZ::LogicalDevice, Image, &MemoryRequirements);

    VkMemoryAllocateInfo AllocateInfo{};
    AllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    AllocateInfo.allocationSize = MemoryRequirements.size;
    AllocateInfo.memoryTypeIndex = SNZ::FindMemoryType(MemoryRequirements.memoryTypeBits, Properties);

    if (vkAllocateMemory(SNZ::LogicalDevice, &AllocateInfo, nullptr, &ImageMemory) != VK_SUCCESS) throw std::runtime_error("Failed to allocate image memory");

    vkBindImageMemory(SNZ::LogicalDevice, Image, ImageMemory, 0);
}