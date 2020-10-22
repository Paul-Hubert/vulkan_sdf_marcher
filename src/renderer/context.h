#ifndef CONTEXT_H
#define CONTEXT_H

#include "windu.h"
#include "input.h"
#include "ui.h"
#include "instance.h"
#include "device.h"
#include "transfer.h"
#include "swapchain.h"
#include "camera.h"
#include "main_render/main_render.h"

class Context {
public:
    Context();
    ~Context();
    
    Windu win;
    Input input;
    UI ui;
    Instance instance;
    Device device;
    Transfer transfer;
    Swapchain swap;
    Camera camera;
    MainRender main_render;
    
    int frame_index = 0;
    int frame_num = 0;
    int semindex = 0;
    std::vector<vk::Semaphore> waitsems;
    std::vector<vk::Semaphore> signalsems;
    std::vector<vk::Semaphore> computesems;
    
};

#endif
