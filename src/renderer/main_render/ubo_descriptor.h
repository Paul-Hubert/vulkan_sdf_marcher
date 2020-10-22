#ifndef UBO_DESCRIPTOR_H
#define UBO_DESCRIPTOR_H

#include "vulkan/vulkan.hpp"

#include "renderer/vmapp.h"

#include "renderer/num_frames.h"

#include "glm/glm.hpp"

struct UBO {
    
    glm::mat4 viewproj;
    
    glm::vec4 viewpos;
    
};

class Context;

class UBODescriptor {
public:
    UBODescriptor(Context& ctx);
    ~UBODescriptor();
    
    vk::DescriptorPool descPool;
    vk::DescriptorSetLayout descLayout;
    std::vector<vk::DescriptorSet> descSets;
    
    std::array<VmaBuffer, NUM_FRAMES> ubos;
    std::array<UBO*, NUM_FRAMES> pointers;
private:
    Context& ctx;
    
};

#endif
