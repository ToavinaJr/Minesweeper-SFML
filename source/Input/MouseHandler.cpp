#include "../../include/Input/MouseHandler.hpp"

namespace Minesweeper {
    MouseHandler::MouseHandler() {
    }

    void MouseHandler::update(const sf::Window& window) {
        mousePosition_ = sf::Mouse::getPosition(window);
        
        // Update button states
        bool leftPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        bool rightPressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);
        
        // Detect clicks (pressed this frame but not last frame)
        leftClicked_ = leftPressed && !wasLeftPressed_;
        rightClicked_ = rightPressed && !wasRightPressed_;
        
        // Update continuous press states
        leftPressed_ = leftPressed;
        rightPressed_ = rightPressed;
        
        // Store previous states
        wasLeftPressed_ = leftPressed;
        wasRightPressed_ = rightPressed;
    }

    sf::Vector2i MouseHandler::getBoardPosition(const sf::Window& window) const {
        sf::Vector2i windowPos = mousePosition_;
        
        // Adjust for UI area
        if (windowPos.y < Config::UI_HEIGHT) {
            return sf::Vector2i(-1, -1); // Clicked in UI area
        }
        
        int boardX = windowPos.x / Config::TILE_SIZE;
        int boardY = (windowPos.y - Config::UI_HEIGHT) / Config::TILE_SIZE;
        
        return sf::Vector2i(boardX, boardY);
    }
}
