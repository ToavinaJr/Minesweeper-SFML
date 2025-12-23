#include "States/PlayingState.hpp"
#include "States/PauseState.hpp"
#include <iostream>

namespace Minesweeper {
    PlayingState::PlayingState(sf::RenderWindow& window, StateManager& stateManager) 
        : StateWithManager(window, stateManager) {  // CORRECTION ICI
        initialize();
    }
    
    void PlayingState::initialize() {
        // Create shared instances
        gameLogic_ = std::make_shared<GameLogic>();
        assetManager_ = std::make_shared<AssetManager>();
        
        // Load assets
        assetManager_->loadAssets();
        
        // Create renderer and input handler
        renderer_ = std::make_shared<Renderer>(gameLogic_, assetManager_);
        inputHandler_ = std::make_shared<InputHandler>(gameLogic_, renderer_);
        uiManager_ = std::make_shared<UIManager>(gameLogic_, assetManager_);
        
        // Start new game
        gameLogic_->startNewGame();
    }
    
    void PlayingState::handleEvents(sf::RenderWindow& window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                // Pause game
                if (event.key.code == sf::Keyboard::Escape ||
                    event.key.code == sf::Keyboard::P) {
                    auto pauseState = std::make_unique<PauseState>(window, stateManager_);
                    stateManager_.pushState(std::move(pauseState));
                }
                // Restart game
                else if (event.key.code == sf::Keyboard::R) {
                    gameLogic_->startNewGame();
                }
            }
            
            // Pass events to input handler for game controls
            inputHandler_->handleEvents(window);
        }
    }
    
    void PlayingState::update(float deltaTime) {
        gameLogic_->update(deltaTime);
        uiManager_->update(deltaTime);
    }
    
    void PlayingState::render(sf::RenderWindow& window) {
        renderer_->render(window);
    }
    
    void PlayingState::onEnter() {
        std::cout << "Entering Playing State" << std::endl;
    }
    
    void PlayingState::onExit() {
        std::cout << "Exiting Playing State" << std::endl;
    }
}