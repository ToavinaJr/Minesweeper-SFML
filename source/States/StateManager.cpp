#include "../include/States/StateManager.hpp"

namespace Minesweeper {
    void StateManager::pushState(std::unique_ptr<GameState> state) {
        if (!states_.empty()) {
            states_.top()->onExit();
        }
        
        states_.push(std::move(state));
        states_.top()->onEnter();
    }

    void StateManager::popState() {
        if (!states_.empty()) {
            states_.top()->onExit();
            states_.pop();
        }
        
        if (!states_.empty()) {
            states_.top()->onEnter();
        }
    }

    void StateManager::changeState(std::unique_ptr<GameState> state) {
        while (!states_.empty()) {
            states_.top()->onExit();
            states_.pop();
        }
        
        states_.push(std::move(state));
        states_.top()->onEnter();
    }

    GameState* StateManager::getCurrentState() {
        if (states_.empty()) {
            return nullptr;
        }
        return states_.top().get();
    }

    void StateManager::handleEvents(sf::RenderWindow& window) {
        if (!states_.empty()) {
            states_.top()->handleEvents(window);
        }
    }

    void StateManager::update(float deltaTime) {
        if (!states_.empty()) {
            states_.top()->update(deltaTime);
        }
    }

    void StateManager::render(sf::RenderWindow& window) {
        if (!states_.empty()) {
            states_.top()->render(window);
        }
    }
}
