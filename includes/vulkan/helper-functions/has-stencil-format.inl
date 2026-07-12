#include "vulkan/helper-functions/has-stencil-component.hpp"

inline bool SNZ::HasStencilComponent(VkFormat Format)
{
    return Format == VK_FORMAT_D32_SFLOAT_S8_UINT || Format == VK_FORMAT_D24_UNORM_S8_UINT;
}