#include "glfw/glfw.hpp"

void SNZ::InitializeGLFW()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    SNZ::Window = glfwCreateWindow(SNZ::WindowWidth, SNZ::WindowHeight, "Vulkan Tutorial", nullptr, nullptr);
}

void SNZ::FreeGLFWResources()
{
    glfwDestroyWindow(SNZ::Window);
    glfwTerminate();
}

