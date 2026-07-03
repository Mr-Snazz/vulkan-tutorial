#include <vector>
#include <set>
#include <string>

#include "vulkan/helper-functions/check-device-extension-support.hpp"

bool SNZ::CheckDeviceExtensionSupport(const VkPhysicalDevice& Device, const std::vector<const char*>& DeviceExtensions)
{
    uint32_t ExtensionCount{};
    vkEnumerateDeviceExtensionProperties(Device, nullptr, &ExtensionCount, nullptr);

    std::vector<VkExtensionProperties> AvailableExtensions(ExtensionCount);
    vkEnumerateDeviceExtensionProperties(Device, nullptr, &ExtensionCount, AvailableExtensions.data());

    std::set<std::string> RequiredExtensions
    (   
        DeviceExtensions.begin(),
        DeviceExtensions.end()
    );

    for (const auto& Extension : AvailableExtensions) {
        RequiredExtensions.erase(Extension.extensionName);
    }

    if (!RequiredExtensions.empty()) return false;

    return true;
}