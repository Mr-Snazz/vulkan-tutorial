#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkan/helper-functions/create-depth-resources.hpp"
#include "vulkan/vulkan.hpp"
#include "vulkan/helper-functions/find-depth-format.hpp"
#include "vulkan/helper-functions/create-image.hpp"
#include "vulkan/helper-functions/create-image-view.hpp"
#include "vulkan/helper-functions/transition-image-layout.hpp"

void SNZ::CreateDepthResources()
{
    VkFormat DepthFormat = SNZ::FindDepthFormat();

    SNZ::CreateImage
    (
        SNZ::SwapChainExtent.width, SNZ::SwapChainExtent.height, 
        DepthFormat, 
        VK_IMAGE_TILING_OPTIMAL, 
        VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, 
        SNZ::DepthImage, 
        SNZ::DepthImageMemory
    );

    SNZ::DepthImageView = SNZ::CreateImageView(SNZ::DepthImage, DepthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);

    SNZ::TransitionImageLayout(SNZ::DepthImage, DepthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);


}