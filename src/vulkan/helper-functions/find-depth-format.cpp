#include "vulkan/helper-functions/find-depth-format.hpp"
#include "vulkan/helper-functions/find-supported-format.hpp"

VkFormat SNZ::FindDepthFormat()
{
    return SNZ::FindSupportedFormat
    (
        { 
            VK_FORMAT_D32_SFLOAT, 
            VK_FORMAT_D32_SFLOAT_S8_UINT, 
            VK_FORMAT_D24_UNORM_S8_UINT 
        },
        VK_IMAGE_TILING_OPTIMAL,
        VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
    );
}