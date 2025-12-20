#pragma once
#include <memory>
#include <stack>
#include "GameState.hpp"

namespace Minesweeper {
    class StateManager {
    public:
        void pushState(std::unique_ptr<GameState> state);
        void popState();
        void changeState(std::unique_ptr<GameState> state);
        
        GameState* getCurrentState();
        
        void handleEvents(sf::RenderWindow& window);
        void update(float deltaTime);
        void render(sf::RenderWindow& window);
        
        bool isEmpty() const { return states_.empty(); }
        
    private:
        std::stack<std::unique_ptr<GameState>> states_;
    };
}
