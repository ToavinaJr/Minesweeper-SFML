#pragma once
#include <SFML/Window.hpp>
#include <memory>
#include "../Logic/GameLogic.hpp"
#include "../Renderer/Renderer.hpp"
#include "MouseHandler.hpp"

namespace Minesweeper {
    class InputHandler {
    public:
        InputHandler(std::shared_ptr<GameLogic> gameLogic, 
                    std::shared_ptr<Renderer> renderer);
        
        void handleEvents(sf::RenderWindow& window);
        void reset();
        
    private:
        std::shared_ptr<GameLogic> gameLogic_;
        std::shared_ptr<Renderer> renderer_;
        MouseHandler mouseHandler_;
        
        void handleMouseEvents(sf::RenderWindow& window);
        void handleKeyboardEvents(const sf::Event& event);
        void handleWindowEvents(const sf::Event& event, sf::RenderWindow& window);
    };
}
