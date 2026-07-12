#pragma one

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace SNZ
{
    VkCommandBuffer BeginSingleTimeCommands();

    void EndSingleTimeCommands(VkCommandBuffer CommandBuffer);
}