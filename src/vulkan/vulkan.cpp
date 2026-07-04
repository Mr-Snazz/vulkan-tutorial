#include <iostream>
#include <cstring>
#include <set>
#include <limits>
#include <algorithm>

#include "vulkan/vulkan.hpp"
#include "glfw/glfw.hpp"
#include "vulkan/queue-family-indices.hpp"
#include "vulkan/helper-functions/swap-chain-support-details.hpp"
#include "vulkan/helper-functions/is-physical-device-suitable.hpp"
#include "vulkan/helper-functions/find-queue-families.hpp"
#include "vulkan/helper-functions/choose-swap-surface-format.hpp"
#include "vulkan/helper-functions/choose-swap-present-mode.hpp"
#include "vulkan/helper-functions/choose-swap-extent.hpp"
#include "vulkan/helper-functions/create-graphics-pipeline.hpp"
#include "vulkan/helper-functions/create-render-pass.hpp"
#include "vulkan/helper-functions/create-framebuffers.hpp"
#include "vulkan/helper-functions/create-command-pool.hpp"
#include "vulkan/helper-functions/create-synchronous-objects.hpp"
#include "vulkan/helper-functions/create-image-views.hpp"
#include "vulkan/helper-functions/create-swapchain.hpp"
#include "vulkan/helper-functions/create-command-buffers.hpp"
#include "vulkan/helper-functions/cleanup-swap-chain.hpp"

const std::vector<const char*> ValidationLayers = 
    {
        "VK_LAYER_KHRONOS_validation"
    };
    #ifdef NDEBUG
        constexpr bool EnableValidationLayers{};
    #else
        constexpr bool EnableValidationLayers{ true };
    #endif

const std::vector<const char*> DeviceExtensions = 
{
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

void SNZ::InitializeVulkan()
{
    VkApplicationInfo ApplicationInfo{};
    ApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    ApplicationInfo.pApplicationName = "Vulkan Triangle";
    ApplicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    ApplicationInfo.pEngineName = "No Engine";
    ApplicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    ApplicationInfo.apiVersion = VK_API_VERSION_1_0;

    uint32_t GLFWExtensionCount{};
    const char** GLFWExtenstions = glfwGetRequiredInstanceExtensions(&GLFWExtensionCount);
    VkInstanceCreateInfo InstaceCreateInfo{};
    InstaceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    InstaceCreateInfo.pApplicationInfo = &ApplicationInfo;
    InstaceCreateInfo.enabledExtensionCount = GLFWExtensionCount;
    InstaceCreateInfo.ppEnabledExtensionNames = GLFWExtenstions;
    InstaceCreateInfo.enabledLayerCount = 0u;

    VkResult Result = vkCreateInstance(&InstaceCreateInfo, nullptr, &SNZ::VulkanInstance);

    if (Result != VK_SUCCESS)
    {
        std::cerr << "Failed to create Vulkan instance!\n";
        exit(EXIT_FAILURE);
    }

    uint32_t ExtensionCount{};
    vkEnumerateInstanceExtensionProperties(nullptr, &ExtensionCount, nullptr);

    std::vector<VkExtensionProperties> Extensions(ExtensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &ExtensionCount, Extensions.data());

    std::cout << "Available Vulkan extensions:\n";
    for (const auto& Extension : Extensions) {
        std::cout << "\t" << Extension.extensionName << "\n";
    }

    // Create surface for rendering
    if (glfwCreateWindowSurface(SNZ::VulkanInstance, SNZ::Window, nullptr, &SNZ::Surface) != VK_SUCCESS) {
        std::cerr << "Failed to create window surface!\n";
        exit(EXIT_FAILURE);
    }

    // Check if all requested validation layers are available
    uint32_t LayerCount{};
    vkEnumerateInstanceLayerProperties(&LayerCount, nullptr);

    std::vector<VkLayerProperties> AvailableLayers(LayerCount);
    vkEnumerateInstanceLayerProperties(&LayerCount, AvailableLayers.data());

    for (const char* LayerName : ValidationLayers) {
        bool LayerFound{};

        for (const auto& LayerProperties : AvailableLayers) {
            if (!strcmp(LayerName, LayerProperties.layerName)) { LayerFound = true; break; }
        }

        if (!LayerFound) {
            std::cerr << "Validation layer not found: " << LayerName << "\n";
            exit(EXIT_FAILURE);
        }
    }

    if (EnableValidationLayers) {
        InstaceCreateInfo.enabledLayerCount = static_cast<uint32_t>(ValidationLayers.size());
        InstaceCreateInfo.ppEnabledLayerNames = ValidationLayers.data();
    } else {
        InstaceCreateInfo.enabledLayerCount = 0u;
    }

    // Choose physical device like a graphics card
    SNZ::PhysicalDevice = VK_NULL_HANDLE;

    uint32_t DeviceCount{};
    vkEnumeratePhysicalDevices(SNZ::VulkanInstance, &DeviceCount, nullptr);

    if (!DeviceCount) {
        std::cerr << "Failed to find GPUs with Vulkan support!\n";
        exit(EXIT_FAILURE);
    }

    std::vector<VkPhysicalDevice> Devices(DeviceCount);
    vkEnumeratePhysicalDevices(SNZ::VulkanInstance, &DeviceCount, Devices.data());

    for (const auto& Device : Devices) {
        if (SNZ::IsPhysicalDeviceSuitable(Device, DeviceExtensions)) {
            SNZ::PhysicalDevice = Device;
            break;
        }
    }

    if (SNZ::PhysicalDevice == VK_NULL_HANDLE) {
        std::cerr << "Failed to find a suitable GPU!\n";
        exit(EXIT_FAILURE);
    }

    //VkPhysicalDeviceProperties DeviceProperties{};
    //vkGetPhysicalDeviceProperties(SNZ::PhysicalDevice, &DeviceProperties);

    // Choose logical device to interface with 
    SNZ::QueueFamilyIndices Indices = SNZ::FindQueueFamilies(SNZ::PhysicalDevice);

    VkDeviceQueueCreateInfo QueueCreateInfo{};
    QueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    QueueCreateInfo.queueFamilyIndex = Indices.GraphicsFamily.value();
    QueueCreateInfo.queueCount = 1u;

    float QueuePriority = 1.0f;
    QueueCreateInfo.pQueuePriorities = &QueuePriority;

    VkPhysicalDeviceFeatures DeviceFeatures{};

    VkDeviceCreateInfo DeviceCreateInfo{};
    DeviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    DeviceCreateInfo.pQueueCreateInfos = &QueueCreateInfo;
    DeviceCreateInfo.queueCreateInfoCount = 1u;
    DeviceCreateInfo.pEnabledFeatures = &DeviceFeatures;

    DeviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(DeviceExtensions.size());
    DeviceCreateInfo.ppEnabledExtensionNames = DeviceExtensions.data();

    if (EnableValidationLayers) {
        DeviceCreateInfo.enabledLayerCount = static_cast<uint32_t>(ValidationLayers.size());
        DeviceCreateInfo.ppEnabledLayerNames = ValidationLayers.data();
    } else {
        DeviceCreateInfo.enabledLayerCount = 0u;
    }

    if (vkCreateDevice(SNZ::PhysicalDevice, &DeviceCreateInfo, nullptr, &SNZ::LogicalDevice) != VK_SUCCESS) {
        std::cerr << "Failed to create logical device!\n";
        exit(EXIT_FAILURE);
    }

    // Retrieve queue handles
    vkGetDeviceQueue(SNZ::LogicalDevice, Indices.GraphicsFamily.value(), 0u, &SNZ::GraphicsQueue);

    // Create presentation queue
    std::vector<VkDeviceQueueCreateInfo> QueueCreateInfos;
    std::set<uint32_t> UniqueQueueFamilies = { Indices.GraphicsFamily.value(), Indices.PresentFamily.value() };

    QueuePriority = 1.0f;
    for (uint32_t QueueFamily : UniqueQueueFamilies) {
        QueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        QueueCreateInfo.queueFamilyIndex = QueueFamily;
        QueueCreateInfo.queueCount = 1u;
        QueueCreateInfo.pQueuePriorities = &QueuePriority;
        QueueCreateInfos.push_back(QueueCreateInfo);
    }

    DeviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(QueueCreateInfos.size());
    DeviceCreateInfo.pQueueCreateInfos = QueueCreateInfos.data();

    vkGetDeviceQueue(SNZ::LogicalDevice, Indices.PresentFamily.value(), 0u, &SNZ::PresentQueue);

    // Create swap chain
    SNZ::CreateSwapchain();

    SNZ::CreateImageViews();

    SNZ::CreateRenderPass();

    SNZ::CreateGraphicsPipeline(SNZ::LogicalDevice);

    SNZ::CreateFramebuffers();
    
    SNZ::CreateCommandPool();

    SNZ::CreateSynchronousObjects();

    SNZ::CreateCommandBuffers();
}

void SNZ::FreeVulkanResources()
{ 
    SNZ::CleanupSwapChain();

    for (uint8_t I{}; I < SNZ::MaxFramesInFlight; ++I) {
        vkDestroySemaphore(SNZ::LogicalDevice, SNZ::ImageAvailableSemaphores[I], nullptr);
        vkDestroySemaphore(SNZ::LogicalDevice, SNZ::RenderFinishedSemaphores[I], nullptr);
        vkDestroyFence    (SNZ::LogicalDevice, SNZ::InFlightFences          [I], nullptr);
    }

    vkDestroyCommandPool(SNZ::LogicalDevice, SNZ::CommandPool, nullptr);

    vkDestroyPipeline(SNZ::LogicalDevice, SNZ::GraphicsPipeline, nullptr);
    vkDestroyPipelineLayout(SNZ::LogicalDevice, SNZ::PipelineLayout, nullptr);
    vkDestroyRenderPass(SNZ::LogicalDevice, SNZ::RenderPass, nullptr);

    vkDestroyDevice(SNZ::LogicalDevice, nullptr);
    vkDestroySurfaceKHR(SNZ::VulkanInstance, SNZ::Surface, nullptr);
    vkDestroyInstance(SNZ::VulkanInstance, nullptr);
}



