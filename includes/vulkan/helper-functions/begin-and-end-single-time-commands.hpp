#pragma one

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace SNZ
{
    VkCommandBuffer BegingSingleTimeCommands();

    void EndSingleTimeCommands(VkCommandBuffer CommandBuffer);
}