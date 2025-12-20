#pragma once
#include <SFML/Graphics.hpp>

namespace Minesweeper {
    class GameState {
    public:
        virtual ~GameState() = default;
        
        virtual void handleEvents(sf::RenderWindow& window) = 0;
        virtual void update(float deltaTime) = 0;
        virtual void render(sf::RenderWindow& window) = 0;
        
        virtual void onEnter() {}
        virtual void onExit() {}
    };
}
