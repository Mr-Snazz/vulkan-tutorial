#include "glfw/framebuffer-resize-callback.hpp"
#include "vulkan/vulkan.hpp"

void SNZ::FramebufferResizeCallback(GLFWwindow* Window, int Width, int Height)
{
    SNZ::FramebufferResized = true;
}