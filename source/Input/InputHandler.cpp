#include "../../include/Input/InputHandler.hpp"
#include <iostream>

namespace Minesweeper {
    InputHandler::InputHandler(std::shared_ptr<GameLogic> gameLogic,
                              std::shared_ptr<Renderer> renderer)
        : gameLogic_(gameLogic), renderer_(renderer) {
    }

    void InputHandler::handleEvents(sf::RenderWindow& window) {
        mouseHandler_.update(window);
        
        sf::Event event;
        while (window.pollEvent(event)) {
            handleWindowEvents(event, window);
            handleKeyboardEvents(event);
        }
        
        handleMouseEvents(window);
    }

    void InputHandler::reset() {
        // Reset mouse handler state if needed
    }

    void InputHandler::handleMouseEvents(sf::RenderWindow& window) {
        if (mouseHandler_.isLeftClicked()) {
            sf::Vector2i mousePos = mouseHandler_.getPosition();
            
            // Check if click is in UI area
            if (mousePos.y < Config::UI_HEIGHT) {
                // Check if face button was clicked
                float faceX = (Config::WINDOW_WIDTH - 70) / 2.0f;
                float faceY = (Config::UI_HEIGHT - 70) / 2.0f + 10; // Ajusté selon le renderer
                
                if (mousePos.x >= faceX && mousePos.x <= faceX + 70 &&
                    mousePos.y >= faceY && mousePos.y <= faceY + 70) {
                    gameLogic_->startNewGame();
                    return;
                }
            } else {
                // Click is on game board
                sf::Vector2i boardPos = mouseHandler_.getBoardPosition(window);
                if (boardPos.x >= 0 && boardPos.y >= 0) {
                    gameLogic_->handleLeftClick(boardPos.x, boardPos.y);
                }
            }
        }
        
        if (mouseHandler_.isRightClicked()) {
            sf::Vector2i boardPos = mouseHandler_.getBoardPosition(window);
            if (boardPos.x >= 0 && boardPos.y >= 0) {
                gameLogic_->handleRightClick(boardPos.x, boardPos.y);
            }
        }
    }

    void InputHandler::handleKeyboardEvents(const sf::Event& event) {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::R:
                case sf::Keyboard::F5:
                    gameLogic_->startNewGame();
                    break;
                    
                case sf::Keyboard::Escape:
                    // Could implement pause menu here
                    break;
                    
                default:
                    break;
            }
        }
    }

    void InputHandler::handleWindowEvents(const sf::Event& event, sf::RenderWindow& window) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
                
            case sf::Event::Resized:
                // Update view to maintain aspect ratio or handle resize
                break;
                
            default:
                break;
        }
    }
}
