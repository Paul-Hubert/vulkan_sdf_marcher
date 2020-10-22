#ifndef UI_RENDER_H
#define UI_RENDER_H

#include "vulkan/vulkan.hpp"
#include "renderer/vmapp.h"

#include "imgui/imgui.h"

#include "renderer/num_frames.h"

class Context;
class Renderpass;

// Frame data
class FrameDataForRender {
public:
    vk::DeviceMemory  vertexBufferMemory;
    vk::DeviceMemory  indexBufferMemory;
    vk::DeviceSize    vertexBufferSize;
    vk::DeviceSize    indexBufferSize;
    vk::Buffer        vertexBuffer;
    vk::Buffer        indexBuffer;
};

class UIRender {
public:
    UIRender(Context& ctx, Renderpass& renderpass);
    ~UIRender();
    
    void createOrResizeBuffer(vk::Buffer& buffer, vk::DeviceMemory& buffer_memory, vk::DeviceSize& p_buffer_size, size_t new_size,vk::BufferUsageFlagBits usage);
    
    void render(vk::CommandBuffer commandBuffer, uint32_t i);
    
    vk::DescriptorPool descPool;
    vk::DescriptorSetLayout descLayout;
    vk::DescriptorSet descSet;
    vk::PipelineLayout pipelineLayout;
    vk::Pipeline graphicsPipeline;
    
    std::array<FrameDataForRender, NUM_FRAMES> g_FramesDataBuffers;
    
    VmaImage fontAtlas;
    vk::ImageView fontView;
    vk::Sampler fontSampler;
    
private:
    
    Context& ctx;
    
    void initPipeline(vk::RenderPass);
    
};

#endif
