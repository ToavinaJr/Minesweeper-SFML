#include "Game/Game.hpp"
#include "States/MainMenuState.hpp"
#include <iostream>

namespace Minesweeper {
    Game::Game() {
        initializeWindow();
        initializeStates();
    }

    Game::~Game() {
        // Cleanup if needed
    }

    void Game::initializeWindow() {
        window_.create(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), 
                      "Minesweeper", sf::Style::Titlebar | sf::Style::Close);
        window_.setFramerateLimit(60);
    }

    void Game::initializeStates() {
        // Start with main menu - passe les 2 arguments requis
        auto mainMenuState = std::make_unique<MainMenuState>(window_, stateManager_);
        stateManager_.pushState(std::move(mainMenuState));
    }

    void Game::run() {
        sf::Clock frameClock;
        
        while (window_.isOpen() && !stateManager_.isEmpty()) {
            float deltaTime = frameClock.restart().asSeconds();
            
            processEvents();
            update(deltaTime);
            render();
        }
    }

    void Game::processEvents() {
        stateManager_.handleEvents(window_);
    }

    void Game::update(float deltaTime) {
        stateManager_.update(deltaTime);
    }

    void Game::render() {
        window_.clear(sf::Color(Config::BACKGROUND_COLOR));
        stateManager_.render(window_);
        window_.display();
    }
}