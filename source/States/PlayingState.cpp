#include "../../include/States/PlayingState.hpp"

namespace Minesweeper {
    PlayingState::PlayingState(sf::RenderWindow& window) {
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
        inputHandler_->handleEvents(window);
    }

    void PlayingState::update(float deltaTime) {
        gameLogic_->update(deltaTime);
        uiManager_->update(deltaTime);
    }

    void PlayingState::render(sf::RenderWindow& window) {
        renderer_->render(window);
    }

    void PlayingState::onEnter() {
        // Reset game when entering this state
        gameLogic_->startNewGame();
    }

    void PlayingState::onExit() {
        // Cleanup if needed
    }
}
