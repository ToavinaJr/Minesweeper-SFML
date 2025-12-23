#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Config.hpp"
#include "../States/StateManager.hpp"
namespace Minesweeper {
    class Game {
    public:
        Game();
        ~Game();
        
        void run();
        
        // Getter for state manager (to pass to states)
        StateManager& getStateManager() { return stateManager_; }
        
    private:
        sf::RenderWindow window_;
        StateManager stateManager_;
        sf::Clock gameClock_;
        
        void initializeWindow();
        void initializeStates();
        void processEvents();
        void update(float deltaTime);
        void render();
    };
}