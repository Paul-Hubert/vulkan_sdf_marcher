#ifndef UI_H
#define UI_H

#include "imgui/imgui.h"
#include <SDL.h>

class Context;

class UI {
public:
    UI(Context& ctx);
    void prepare();
    ~UI();
private:
    Context& ctx;
    SDL_Cursor* g_MouseCursors[ImGuiMouseCursor_COUNT] = {0};
    Uint64 g_Time = 0;
};

#endif
