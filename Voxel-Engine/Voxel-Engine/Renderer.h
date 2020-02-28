#pragma once

#include <iostream>
#include <vector>

#include "vulkan/vulkan.h"

#define ASSERT_VULKAN(val)                              \
    if (val != VK_SUCCESS)                              \
    {                                                   \
        std::cout << "A problem occured." << std::endl; \
        return;                                         \
    }

namespace LLR {

    VkInstance instance;

    VkLayerProperties* layers;
    VkExtensionProperties* extensions;
    VkPhysicalDevice* physicalDevices;

    VkDevice device;


    void init()
    {
        std::cout << "starting programm..." << std::endl;

        VkApplicationInfo appInfo;
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pNext = NULL;
        appInfo.pApplicationName = "Vulkan Test";
        appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
        appInfo.pEngineName = "Voxel engine";
        appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_1;

        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, NULL);
        layers = new VkLayerProperties[layerCount];
        vkEnumerateInstanceLayerProperties(&layerCount, layers);

        for (uint32_t i = 0; i < layerCount; i++)
        {
            VkLayerProperties* currentLayerProperty = &layers[i];
            std::cout << currentLayerProperty->layerName << ": " << currentLayerProperty->description << std::endl;
            std::cout << "Implementation version:               " << currentLayerProperty->implementationVersion << std::endl;
            std::cout << "Spec. version:                        " << currentLayerProperty->specVersion << std::endl;
            std::cout << std::endl;
        }

        const std::vector<const char*> validationLayers = {
            "VK_LAYER_LUNARG_standard_validation"
        };

        uint32_t extensionsCount = 0;
        vkEnumerateInstanceExtensionProperties(NULL, &extensionsCount, NULL);
        extensions = new VkExtensionProperties[extensionsCount];
        vkEnumerateInstanceExtensionProperties(NULL, &extensionsCount, extensions);

        for (uint32_t i = 0; i < extensionsCount; i++)
        {
            VkExtensionProperties* currentExtensionProperty = &extensions[i];
            std::cout
                << std::endl;
            std::cout << currentExtensionProperty->extensionName << ":" << std::endl;
            std::cout << "Spec. version:                        " << currentExtensionProperty->specVersion << std::endl;
        }


        VkInstanceCreateInfo instanceInfo;
        instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceInfo.pNext = NULL;
        instanceInfo.flags = 0;
        instanceInfo.pApplicationInfo = &appInfo;
        instanceInfo.enabledLayerCount = validationLayers.size();
        instanceInfo.ppEnabledLayerNames = validationLayers.data();
        instanceInfo.enabledExtensionCount = 0;
        instanceInfo.ppEnabledExtensionNames = NULL;

        VkResult result = vkCreateInstance(&instanceInfo, NULL, &instance); // learn about allucations

        ASSERT_VULKAN(result);

        uint32_t physicalDevicesCount = 0;
        result = vkEnumeratePhysicalDevices(instance, &physicalDevicesCount, NULL);
        ASSERT_VULKAN(result);

        physicalDevices = new VkPhysicalDevice[physicalDevicesCount];
        result = vkEnumeratePhysicalDevices(instance, &physicalDevicesCount, physicalDevices);
        ASSERT_VULKAN(result);

        VkPhysicalDevice currentDevice = physicalDevices[0];

        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(currentDevice, &properties);

        std::cout << "Device name:                          " << properties.deviceName << std::endl;
        std::cout << "Device type:                          " << properties.deviceType << std::endl;
        std::cout << "Device id:                            " << properties.deviceID << std::endl;
        std::cout << "Driver version:                       " << properties.driverVersion << std::endl;
        std::cout << "api version:                          " << properties.apiVersion << std::endl;
        std::cout << std::endl;

        VkPhysicalDeviceFeatures feature;
        vkGetPhysicalDeviceFeatures(currentDevice, &feature);

        std::cout << "Geometry shader:                      " << feature.geometryShader << std::endl;
        std::cout << "Depth clamp:                          " << feature.depthClamp << std::endl;
        std::cout << "Image cube array:                     " << feature.imageCubeArray << std::endl;
        std::cout << std::endl;

        VkPhysicalDeviceMemoryProperties memoryProperties;
        vkGetPhysicalDeviceMemoryProperties(currentDevice, &memoryProperties);

        uint16_t memoryHeapCount = memoryProperties.memoryHeapCount;

        std::cout << "Memory heaps:                         " << memoryHeapCount << std::endl;

        for (int i = 0; i < memoryHeapCount; i++)
        {
            uint64_t size = memoryProperties.memoryHeaps[i].size / 1000000000;
            std::cout << "Memory size [" << i << "]:                      " << size << " GB" << std::endl;
        }
        std::cout << std::endl;

        uint32_t queueFamiliesCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(currentDevice, &queueFamiliesCount, NULL);
        VkQueueFamilyProperties* queueFamilieProperties = new VkQueueFamilyProperties[queueFamiliesCount];
        vkGetPhysicalDeviceQueueFamilyProperties(currentDevice, &queueFamiliesCount, queueFamilieProperties);

        std::cout << "Amount of Queue Families:             " << queueFamiliesCount << std::endl;

        for (int i = 0; i < queueFamiliesCount; i++)
        {
            VkQueueFamilyProperties* properties = &queueFamilieProperties[i];
            std::cout << std::endl;
            std::cout << "Queue Familie #" << (i + 1) << std::endl;
            std::cout << "Count:                                " << properties->queueCount << std::endl;
            std::cout << "Graphics bit:                         " << (properties->queueFlags & VK_QUEUE_GRAPHICS_BIT) << std::endl;
            std::cout << "Compute bit:                          " << (properties->queueFlags & VK_QUEUE_COMPUTE_BIT) << std::endl;
            std::cout << "Transfer bit:                         " << (properties->queueFlags & VK_QUEUE_TRANSFER_BIT) << std::endl;
            std::cout << "Sparse Binding bit:                   " << (properties->queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) << std::endl;
        }

        uint32_t queueFamiliyIndex = 0; //TODO: choose best queue familie

        //TODO: set this up properly
        float queuePrios[] = {
            1.0f, 1.0f, 1.0f, 1.0f
        };

        VkDeviceQueueCreateInfo deviceQueueCreateInfo;
        deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        deviceQueueCreateInfo.pNext = NULL;
        deviceQueueCreateInfo.flags = 0;
        deviceQueueCreateInfo.queueFamilyIndex = queueFamiliyIndex;
        deviceQueueCreateInfo.queueCount = queueFamilieProperties[queueFamiliyIndex].queueCount;
        deviceQueueCreateInfo.pQueuePriorities = queuePrios;

        VkPhysicalDeviceFeatures usedFeatures = {};

        VkDeviceCreateInfo deviceCreateInfo;
        deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateInfo.pNext = NULL;
        deviceCreateInfo.flags = 0;
        deviceCreateInfo.queueCreateInfoCount = 1;
        deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
        deviceCreateInfo.enabledLayerCount = 0;
        deviceCreateInfo.ppEnabledLayerNames = NULL;
        deviceCreateInfo.enabledExtensionCount = 0;
        deviceCreateInfo.ppEnabledExtensionNames = NULL;
        deviceCreateInfo.pEnabledFeatures = &usedFeatures;

        uint32_t phyiscalDeviceIndex = 0; //TODO pick best device

        result = vkCreateDevice(physicalDevices[phyiscalDeviceIndex], &deviceCreateInfo, NULL, &device);
        ASSERT_VULKAN(result);

        VkQueue queue;
        vkGetDeviceQueue(device, queueFamiliyIndex, 0, &queue);
    }

    void terminate() {
        vkDeviceWaitIdle(device);
        vkDestroyDevice(device, NULL);
        vkDestroyInstance(instance, NULL);

        delete[] layers;
        delete[] extensions;
        delete[] physicalDevices;
    }
}