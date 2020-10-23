#include "main_render.h"

#include "renderer/context.h"
#include "util/util.h"
#include "renderer/num_frames.h"

MainRender::MainRender(Context& ctx) : renderpass(ctx), ubo(ctx), ray_marcher(ctx), ui_render(ctx), ctx(ctx) {
    
    commandPool = ctx.device->createCommandPool(vk::CommandPoolCreateInfo(vk::CommandPoolCreateFlagBits::eResetCommandBuffer, ctx.device.g_i));
    
    auto temp = ctx.device->allocateCommandBuffers(vk::CommandBufferAllocateInfo(commandPool, vk::CommandBufferLevel::ePrimary, NUM_FRAMES));
    
    for(size_t i = 0; i < NUM_FRAMES; i++) {
        
        commandBuffers[i] = temp[i];
        
        fences[i] = ctx.device->createFence(vk::FenceCreateInfo(vk::FenceCreateFlagBits::eSignaled));
        
    }
    
}


void MainRender::setup() {
    
    renderpass.setup();
    
}

void MainRender::render(uint32_t index, std::vector<vk::Semaphore> waits, std::vector<vk::Semaphore> signals) {
    
    
    ctx.device->waitForFences(fences[ctx.frame_index], VK_TRUE, std::numeric_limits<uint64_t>::max());
    
    ctx.device->resetFences(fences[ctx.frame_index]);
    
    static float t = 0.f;
    t += 1.f/60.f;
    
    ubo.pointers[ctx.frame_index]->viewproj = ctx.camera.getViewProjection();
    ubo.pointers[ctx.frame_index]->viewpos = glm::vec4(ctx.camera.getViewPosition(), t);
    ubo.pointers[ctx.frame_index]->screensize = glm::vec2(ctx.swap.extent.width, ctx.swap.extent.height);
    
    vk::CommandBuffer command = commandBuffers[ctx.frame_index];
        
    command.begin(vk::CommandBufferBeginInfo({}, nullptr));
    
    auto clearValues = std::vector<vk::ClearValue> {
        vk::ClearValue(vk::ClearColorValue(std::array<float, 4> { 0.2f, 0.2f, 0.2f, 1.0f })),
        vk::ClearValue(vk::ClearDepthStencilValue(1.0f, 0))};
    command.beginRenderPass(vk::RenderPassBeginInfo(renderpass, renderpass.framebuffers[index], vk::Rect2D({}, ctx.swap.extent), clearValues.size(), clearValues.data()), vk::SubpassContents::eInline);
    
    command.setViewport(0, vk::Viewport(0, (float) ctx.swap.extent.height, ctx.swap.extent.width, -((float) ctx.swap.extent.height), 0, 1));
    
    command.setScissor(0, vk::Rect2D(vk::Offset2D(), ctx.swap.extent));
    
    ray_marcher.render(command);
    
    ui_render.render(command);
    
    command.endRenderPass();
    
    command.end();
    

    auto stages = std::vector<vk::PipelineStageFlags> {vk::PipelineStageFlagBits::eTopOfPipe, vk::PipelineStageFlagBits::eTopOfPipe};
    
    ctx.device.graphics.submit({vk::SubmitInfo(
        Util::removeElement<vk::Semaphore>(waits, nullptr), waits.data(), stages.data(),
        1, &commandBuffers[ctx.frame_index],
        Util::removeElement<vk::Semaphore>(signals, nullptr), signals.data()
    )}, fences[ctx.frame_index]);
    
}

void MainRender::cleanup() {
    
    ctx.device->resetCommandPool(commandPool, {});
    renderpass.cleanup();
    
}


MainRender::~MainRender() {
    
    for(size_t i = 0; i < commandBuffers.size(); i++) {
        
        ctx.device->destroy(fences[i]);
        
    }
    
    ctx.device->destroy(commandPool);
    
}
