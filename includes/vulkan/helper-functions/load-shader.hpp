#pragma once

#include <vector>
#include <string>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace SNZ
{
    constexpr const char* CompiledShaderDirectory = "compiled-shaders/";

    std::vector<char> LoadShader(const std::string& FileName);

    VkShaderModule CreateShaderModule(const VkDevice& LogicalDevice, const std::vector<char>& Code);
}