#include "Game/Game.hpp"
#include "States/PlayingState.hpp"
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
        // Start with playing state
        auto playingState = std::make_unique<PlayingState>(window_);
        stateManager_.pushState(std::move(playingState));
    }

    void Game::run() {
        sf::Clock frameClock;
        
        while (window_.isOpen() && !stateManager_.isEmpty()) {
            float deltaTime = frameClock.restart().asSeconds();
            
            processEvents();
            update(deltaTime); // CHANGEMENT ICI : passe deltaTime en paramètre
            render();
        }
    }

    void Game::processEvents() {
        stateManager_.handleEvents(window_);
    }

    void Game::update(float deltaTime) { // CHANGEMENT ICI : ajout du paramètre
        stateManager_.update(deltaTime);
    }

    void Game::render() {
        window_.clear(sf::Color(Config::BACKGROUND_COLOR));
        stateManager_.render(window_);
        window_.display();
    }
}