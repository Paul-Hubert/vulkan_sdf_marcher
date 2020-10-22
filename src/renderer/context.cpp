#include "context.h"

Context::Context() : win(), input(*this), ui(*this), instance(*this), device(*this), transfer(*this), swap(*this), camera(swap.extent.width, swap.extent.height), main_render(*this), waitsems(swap.num_frames), signalsems(swap.num_frames), computesems(swap.num_frames) {
    
    for(size_t i = 0; i < waitsems.size(); i++) {
        waitsems[i] = device->createSemaphore({});
        SET_NAME(vk::ObjectType::eSemaphore, (VkSemaphore) waitsems[i], wait)
        signalsems[i] = device->createSemaphore({});
        SET_NAME(vk::ObjectType::eSemaphore, (VkSemaphore) signalsems[i], signal)
        computesems[i] = device->createSemaphore({});
        SET_NAME(vk::ObjectType::eSemaphore, (VkSemaphore) computesems[i], compute)
    }
    
}

Context::~Context() {
    
    for(size_t i = 0; i < waitsems.size(); i++) {
        device->destroy(waitsems[i]);
        device->destroy(signalsems[i]);
        device->destroy(computesems[i]);
    }
    
}
