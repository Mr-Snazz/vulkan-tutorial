#include <fstream>

#include "vulkan/helper-functions/load-shader.hpp"

std::vector<char> SNZ::LoadShader(const std::string& FileName)
{
    std::ifstream File(SNZ::CompiledShaderDirectory + FileName, std::ios::ate | std::ios::binary);
    
    if (!File.is_open()) throw std::runtime_error("Failed to open shader file: " + FileName);

    size_t FileSize = static_cast<size_t>(File.tellg());
    std::vector<char> Buffer(FileSize);

    File.seekg(0);
    File.read(Buffer.data(), FileSize);
    File.close();

    return Buffer;
}

VkShaderModule SNZ::CreateShaderModule(const VkDevice& LogicalDevice, const std::vector<char>& Code)
{
    VkShaderModuleCreateInfo CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    CreateInfo.codeSize = Code.size();
    CreateInfo.pCode = reinterpret_cast<const uint32_t*>(Code.data());

    VkShaderModule ShaderModule{};
    if (vkCreateShaderModule(LogicalDevice, &CreateInfo, nullptr, &ShaderModule) != VK_SUCCESS) throw std::runtime_error("Failed to create shader module");

    return ShaderModule;
}