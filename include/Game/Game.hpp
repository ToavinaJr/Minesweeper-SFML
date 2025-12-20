#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../States/StateManager.hpp"

namespace Minesweeper {
    class Game {
    public:
        Game();
        ~Game();
        
        void run();
        
    private:
        sf::RenderWindow window_;
        StateManager stateManager_;
        sf::Clock gameClock_;
        
        void initializeWindow();
        void initializeStates();
        void processEvents();
        void update(float deltaTime); // CHANGEMENT ICI : ajout du paramètre deltaTime
        void render();
    };
}