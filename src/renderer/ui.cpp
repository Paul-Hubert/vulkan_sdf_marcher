#include "ui.h"

#include "context.h"

UI::UI(Context& ctx) : ctx(ctx) {
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    auto& io = ImGui::GetIO(); (void) io;
    io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("./resources/fonts/aniron.ttf", 50.0f, NULL, io.Fonts->GetGlyphRangesDefault());
    
    io.IniFilename = nullptr;

    g_MouseCursors[ImGuiMouseCursor_Arrow] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    g_MouseCursors[ImGuiMouseCursor_TextInput] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
    g_MouseCursors[ImGuiMouseCursor_ResizeAll] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
    g_MouseCursors[ImGuiMouseCursor_ResizeNS] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
    g_MouseCursors[ImGuiMouseCursor_ResizeEW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
    g_MouseCursors[ImGuiMouseCursor_ResizeNESW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENESW);
    g_MouseCursors[ImGuiMouseCursor_ResizeNWSE] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENWSE);
    g_MouseCursors[ImGuiMouseCursor_Hand] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    
}

void UI::prepare() {
    
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange)
        return;

    ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
    if (!ctx.input.mouseFree || io.MouseDrawCursor || imgui_cursor == ImGuiMouseCursor_None)
    {
        // Hide OS mouse cursor if imgui is drawing it or if it wants no cursor
        SDL_ShowCursor(SDL_FALSE);
    }
    else
    {
        // Show OS mouse cursor
        SDL_SetCursor(g_MouseCursors[imgui_cursor] ? g_MouseCursors[imgui_cursor] : g_MouseCursors[ImGuiMouseCursor_Arrow]);
        SDL_ShowCursor(SDL_TRUE);
    }
    
    io.MouseDown[0] = ctx.input.mouseLeft || ctx.input.on[Action::PRIMARY];
    io.MouseDown[1] = ctx.input.mouseRight || ctx.input.on[Action::SECONDARY];
    io.MouseDown[2] = ctx.input.mouseMiddle || ctx.input.on[Action::TERTIARY];

    if(ctx.input.focused)
        io.MousePos = ImVec2(ctx.input.mousePos.x, ctx.input.mousePos.y);
    
    
    if (!(io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange)) {

        ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
        if (!ctx.input.mouseFree || io.MouseDrawCursor || imgui_cursor == ImGuiMouseCursor_None)
        {
            // Hide OS mouse cursor if imgui is drawing it or if it wants no cursor
            SDL_ShowCursor(SDL_FALSE);
        }
        else
        {
            // Show OS mouse cursor
            SDL_SetCursor(g_MouseCursors[imgui_cursor] ? g_MouseCursors[imgui_cursor] : g_MouseCursors[ImGuiMouseCursor_Arrow]);
            SDL_ShowCursor(SDL_TRUE);
        }
        
    }
    
    int w, h;
    SDL_GetWindowSize(ctx.win, &w, &h);
    io.DisplaySize = ImVec2((float)w, (float)h);
    
    static Uint64 frequency = SDL_GetPerformanceFrequency();
    Uint64 current_time = SDL_GetPerformanceCounter();
    io.DeltaTime = g_Time > 0 ? (float)((double)(current_time - g_Time) / frequency) : (float)(1.0f / 60.0f);
    g_Time = current_time;
    
    ImGui::NewFrame();
    
}

UI::~UI() {
    
    for (ImGuiMouseCursor cursor_n = 0; cursor_n < ImGuiMouseCursor_COUNT; cursor_n++)
        SDL_FreeCursor(g_MouseCursors[cursor_n]);
    memset(g_MouseCursors, 0, sizeof(g_MouseCursors));
    
}
