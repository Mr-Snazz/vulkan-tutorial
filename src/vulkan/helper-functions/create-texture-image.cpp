#include <stdint.h>

#include <stdexcept>
#include <cstring>

#include "stb_image.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkan/helper-functions/create-texture-image.hpp"
#include "vulkan/helper-functions/create-buffer.hpp"
#include "vulkan/vulkan.hpp"
#include "vulkan/helper-functions/find-memory-type.hpp"
#include "vulkan/helper-functions/create-image.hpp"
#include "vulkan/helper-functions/transition-image-layout.hpp"
#include "vulkan/helper-functions/copy-buffer-to-image.hpp"

void SNZ::CreateTextureImage()
{
    int32_t Width, Height, Channels;
    uint8_t* Pixels = stbi_load("textures/chudjak.png", &Width, &Height, &Channels, STBI_rgb_alpha);

    if (!Pixels) throw std::runtime_error("Failed to laod texture image");

    VkDeviceSize ImageSize = Width * Height * 4;

    VkBuffer StagingBuffer{};
    VkDeviceMemory StagingBufferMemory{};

    SNZ::CreateBuffer(ImageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, StagingBuffer, StagingBufferMemory);

    void* Data{};
    vkMapMemory(SNZ::LogicalDevice, StagingBufferMemory, 0, ImageSize, 0, &Data);
    std::memcpy(Data, Pixels, static_cast<size_t>(ImageSize));
    vkUnmapMemory(SNZ::LogicalDevice, StagingBufferMemory);

    stbi_image_free(Pixels);

    SNZ::CreateImage(Width, Height, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, TextureImage, TextureImageMemory);

    SNZ::TransitionImageLayout(TextureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    SNZ::CopyBufferToImage(StagingBuffer, TextureImage, static_cast<uint32_t>(Width), static_cast<uint32_t>(Height));

    SNZ::TransitionImageLayout(TextureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

    vkDestroyBuffer(SNZ::LogicalDevice, StagingBuffer, nullptr);
    vkFreeMemory(SNZ::LogicalDevice, StagingBufferMemory, nullptr);
}