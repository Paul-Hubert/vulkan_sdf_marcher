#include "game.h"

#include <iostream>

#include "renderer/renderer.h"

Game::Game(int argc, char** argv) : renderer(std::make_unique<Renderer>()) {
    
}

void Game::init() {
    
}

void Game::start() {
    
    game_loop.run([this](float dt) {
        
        renderer->prerender();
        
        if(renderer->ctx.input.on[Action::EXIT]) {
            game_loop.setQuitting();
        }
        
        renderer->render();
        
    });
    
}

Game::~Game() {
    
}
