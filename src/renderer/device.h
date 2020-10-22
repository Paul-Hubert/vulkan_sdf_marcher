#ifndef DEVICE_H
#define DEVICE_H

#include <vulkan/vulkan.hpp>
#include "vma/vk_mem_alloc.h"
#include <mutex>

class Context;

#ifndef NDEBUG
#define SET_NAME(TYPE, HANDLE, STR) \
device->setDebugUtilsObjectNameEXT(vk::DebugUtilsObjectNameInfoEXT(TYPE, (uint64_t) HANDLE, #STR), device);
#else
#define SET_NAME(TYPE, HANDLE, STR)
#endif

class Device {
public :
    Device(Context& ctx);
    ~Device();
    
    vk::Device* operator->() {return &logical;}
    operator vk::Device() { return logical; }
    operator VkDevice() { return static_cast<VkDevice>(logical); }
    operator vk::PhysicalDevice() { return physical; }
    operator VkPhysicalDevice() { return static_cast<VkPhysicalDevice>(physical); }
    operator VmaAllocator() { return allocator; }
    
    uint32_t getScore(vk::PhysicalDevice &device);
    uint32_t getMemoryType(uint32_t typeBits, vk::MemoryPropertyFlags properties);
    
    bool isDedicated();
    
    vk::Queue graphics, compute, transfer;
    uint32_t g_i = 0, c_i = 0, t_i = 0;
    std::mutex *g_mutex, *c_mutex, *t_mutex;
    std::unique_ptr<std::mutex> g_mutex_, c_mutex_, t_mutex_;
    
    vk::PhysicalDeviceFeatures requiredFeatures;
    std::vector<const char*> requiredExtensions;
    
    vk::PhysicalDeviceProperties properties;
    vk::PhysicalDeviceFeatures features;
    vk::PhysicalDeviceMemoryProperties memoryProperties;
    std::vector<vk::QueueFamilyProperties> queueFamilies;
    std::vector<vk::ExtensionProperties> extensions;
    
    vk::PhysicalDevice physical;
    vk::Device logical;
    VmaAllocator allocator;
    
    PFN_vkSetDebugUtilsObjectNameEXT vkSetDebugUtilsObjectNameEXT;
    
private:
    Context& ctx;
};

#endif
