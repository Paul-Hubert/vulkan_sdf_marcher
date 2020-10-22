#ifndef INPUT_H
#define INPUT_H

#include <bitset>
#include "glm/glm.hpp"
#include "SDL.h"

class Context;

enum Action : char {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    SPRINT,
    PRIMARY,
    SECONDARY,
    TERTIARY,
    RESIZE,
    MENU,
    DEBUG,
    EXIT,
    END_ENUM
};

class Input {
public:
    Input(Context& ctx);
    void capture();
    
    std::bitset<Action::END_ENUM> on;
    bool mouseFree = false;
    glm::ivec2 mousePos;
    glm::ivec2 mouseDiff;
    glm::ivec2 mouseWheel;
    bool mouseLeft = false;
    bool mouseRight = false;
    bool mouseMiddle = false;
    bool focused = true;
    
private:
    Context& ctx;
};

#endif

