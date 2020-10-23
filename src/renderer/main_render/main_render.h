#ifndef MAIN_RENDER_H
#define MAIN_RENDER_H

#include "renderpass.h"
#include "ubo_descriptor.h"
#include "ray_marcher.h"
#include "ui_render.h"

#include "renderer/vmapp.h"

#include "renderer/num_frames.h"

#include <vector>

class Context;

class MainRender {
public:
    MainRender(Context& ctx);
    void setup();
    void render(uint32_t index, std::vector<vk::Semaphore> waits, std::vector<vk::Semaphore> signals);
    void cleanup();
    ~MainRender();
    
    
    Renderpass renderpass;
    
    UBODescriptor ubo;
    
    RayMarcher ray_marcher;
    
    UIRender ui_render;
    
private:
    Context& ctx;
    
    vk::CommandPool commandPool;
    std::array<vk::CommandBuffer, NUM_FRAMES> commandBuffers;
    std::array<vk::Fence, NUM_FRAMES> fences;
    
};

#endif
