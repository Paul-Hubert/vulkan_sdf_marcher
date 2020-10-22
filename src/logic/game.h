#ifndef GAME_H
#define GAME_H

#include <memory>
#include "util/game_loop.h"

class Renderer;

class Game {
public:
    Game(int argc, char** argv);
    void init();
    void start();
    ~Game();
    
    GameLoop game_loop;
    
    std::unique_ptr<Renderer> renderer;
    
};

#endif
