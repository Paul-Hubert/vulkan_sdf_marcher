#ifndef INSTANCE_H
#define INSTANCE_H

#include <vulkan/vulkan.hpp>

class Context;

class Instance {
public:
    Instance(Context& ctx);
    ~Instance();
    vk::Instance* operator->() {return &instance;}
    operator vk::Instance() { return instance; }
    operator VkInstance() { return static_cast<VkInstance>(instance); }
    bool supportsPresent(VkPhysicalDevice device, int i);
    VkDebugUtilsMessengerEXT messenger;
private:
    vk::Instance instance;
    Context& ctx;
    PFN_vkGetPhysicalDeviceSurfaceSupportKHR vkGetPhysicalDeviceSurfaceSupportKHR;
};

#endif
