#ifndef RAY_MARCHER_H
#define RAY_MARCHER_H

#include "renderer/vmapp.h"

class Context;

class RayMarcher {
public:
    RayMarcher(Context& ctx);
    void render(vk::CommandBuffer commandBuffer);
    ~RayMarcher();
private:
    void initPipeline();
    
    vk::DescriptorPool descPool;
    vk::DescriptorSetLayout descLayout;
    vk::DescriptorSet descSet;
    vk::PipelineLayout pipelineLayout;
    vk::Pipeline pipeline;
    
    Context& ctx;
};

#endif
