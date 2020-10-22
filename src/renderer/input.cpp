#include "input.h"

#include <SDL.h>

#include <iostream>

#include <unordered_map>

#include "context.h"

std::unordered_map<SDL_Scancode, Action> actionMap = {
    {SDL_SCANCODE_W, Action::FORWARD},
    {SDL_SCANCODE_S, Action::BACKWARD},
    {SDL_SCANCODE_A, Action::LEFT},
    {SDL_SCANCODE_D, Action::RIGHT},
    {SDL_SCANCODE_LCTRL, Action::SPRINT},
    {SDL_SCANCODE_SPACE, Action::UP},
    {SDL_SCANCODE_LSHIFT, Action::DOWN},
    {SDL_SCANCODE_M, Action::MENU},
    {SDL_SCANCODE_K, Action::DEBUG}
};

Input::Input(Context& ctx) : ctx(ctx) {
    
    int w, h;
    SDL_GetWindowSize(ctx.win, &w, &h);
    SDL_WarpMouseInWindow(ctx.win, w / 2, h / 2);
    mouseFree = true;
    
}

void Input::capture() {
    
    mouseRight = mouseLeft = mouseMiddle = false;

    auto flags = SDL_GetWindowFlags(ctx.win);

    focused = flags & SDL_WINDOW_MOUSE_FOCUS;
    
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        
        if(e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED) {
            
            on.set(Action::RESIZE);
            
        } else if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)) {
            
            on.set(Action::EXIT);
            
        } else if(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
            
            try {
                on.set(actionMap.at(e.key.keysym.scancode), e.type == SDL_KEYDOWN);
            } catch(std::out_of_range& err) {}
            
        } else if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
            
            switch(e.button.button) {
                case SDL_BUTTON_LEFT:
                    on.set(Action::PRIMARY, e.type == SDL_MOUSEBUTTONDOWN);
                    if(e.type == SDL_MOUSEBUTTONDOWN) mouseLeft = true;
                    break;
                case SDL_BUTTON_RIGHT:
                    on.set(Action::SECONDARY, e.type == SDL_MOUSEBUTTONDOWN);
                    if(e.type == SDL_MOUSEBUTTONDOWN) mouseRight = true;
                    break;
                case SDL_BUTTON_MIDDLE:
                    on.set(Action::TERTIARY, e.type == SDL_MOUSEBUTTONDOWN);
                    if(e.type == SDL_MOUSEBUTTONDOWN) mouseMiddle = true;
                    break;
            }
            
        } if(e.type == SDL_MOUSEWHEEL) {
            
            if (e.wheel.x > 0) mouseWheel.x += 1;
            else if (e.wheel.x < 0) mouseWheel.x -= 1;
            if (e.wheel.y > 0) mouseWheel.y += 1;
            else if (e.wheel.y < 0) mouseWheel.y -= 1;
            
        }
        
    }
    
    if (focused) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        
        int w, h;
        SDL_GetWindowSize(ctx.win, &w, &h);
        if(!mouseFree) SDL_WarpMouseInWindow(ctx.win, w / 2, h / 2);
        
        mousePos = glm::ivec2(x, y);
        mouseDiff = glm::ivec2(x - w / 2, y - h / 2);
    }
    
}
