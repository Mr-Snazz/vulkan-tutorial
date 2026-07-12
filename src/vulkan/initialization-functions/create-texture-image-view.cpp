#include <stdexcept>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkan/initialization-functions/create-texture-image-view.hpp"
#include "vulkan/vulkan.hpp"
#include "vulkan/helper-functions/create-image-view.hpp"

void SNZ::CreateTextureImageView()
{
    SNZ::TextureImageView = SNZ::CreateImageView(SNZ::TextureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT, SNZ::MipLevels);
}