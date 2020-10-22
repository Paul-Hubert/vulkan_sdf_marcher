#include "renderer.h"

#include <iostream>

#include "num_frames.h"

Renderer::Renderer() {
    
    ctx.main_render.setup();
    
    ctx.transfer.flush();
    
}

void Renderer::prerender() {
    
    ctx.frame_index = (ctx.frame_index+1)%ctx.swap.num_frames;
    ctx.frame_num++;
    
    ctx.input.capture();
    
    ctx.ui.prepare();
    
    if(ctx.input.on[Action::RESIZE]) {
        resize();
        ctx.input.on.set(Action::RESIZE, false);
    }
    
}

void Renderer::render() {
    
    try {
        
        ctx.transfer.flush();
        
        ctx.camera.update();
        
        uint32_t index = ctx.swap.acquire(ctx.waitsems[ctx.frame_index]);
        
        ctx.main_render.render(index, {ctx.waitsems[ctx.frame_index]}, {ctx.signalsems[ctx.frame_index]});
        
        ctx.swap.present(ctx.signalsems[ctx.frame_index]);
        
    } catch(vk::OutOfDateKHRError&) {
        
        resize();
        
    }
    
}

Renderer::~Renderer() {
    
    ctx.device->waitIdle();
    
    ctx.main_render.cleanup();
    
}

void Renderer::resize() {
    
    if(ctx.win.resize()) {
        
        ctx.device->waitIdle();
        
        ctx.main_render.cleanup();
        
        ctx.swap.cleanup();
        
        ctx.swap.setup();
        
        ctx.camera.setup(ctx.swap.extent.width, ctx.swap.extent.height);
        
        ctx.main_render.setup();
    
    }
    
}
