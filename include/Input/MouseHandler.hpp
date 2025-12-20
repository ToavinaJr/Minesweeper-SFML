#pragma once
#include <SFML/Window.hpp>
#include "../Game/Config.hpp"

namespace Minesweeper {
    class MouseHandler {
    public:
        MouseHandler();
        
        // Mouse state
        void update(const sf::Window& window);
        
        // Button checks
        bool isLeftClicked() const { return leftClicked_; }
        bool isRightClicked() const { return rightClicked_; }
        bool isLeftPressed() const { return leftPressed_; }
        bool isRightPressed() const { return rightPressed_; }
        
        // Position
        sf::Vector2i getPosition() const { return mousePosition_; }
        sf::Vector2i getBoardPosition(const sf::Window& window) const;
        
    private:
        sf::Vector2i mousePosition_;
        bool leftPressed_ = false;
        bool rightPressed_ = false;
        bool leftClicked_ = false;
        bool rightClicked_ = false;
        
        bool wasLeftPressed_ = false;
        bool wasRightPressed_ = false;
    };
}
