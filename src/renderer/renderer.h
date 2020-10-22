#ifndef RENDERER_H
#define RENDERER_H

#include "context.h"

class Renderer {
public:
    Renderer();
    void prerender();
    void render();
    ~Renderer();
    
    void resize();
    
    Context ctx;
};

#endif
