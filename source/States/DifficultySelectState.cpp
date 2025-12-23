#include "States/DifficultySelectState.hpp"
#include "States/PlayingState.hpp"
#include "Game/Config.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

namespace Minesweeper {
    DifficultySelectState::DifficultySelectState(sf::RenderWindow& window, StateManager& stateManager) 
        : StateWithManager(window, stateManager) {
        
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        
        if (!font_.loadFromFile("assets/fonts/arial.ttf")) {
            std::cerr << "Failed to load font in DifficultySelectState" << std::endl;
            font_.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
        }
        
        createBackground();
        initializeMenu();
    }
    
    void DifficultySelectState::createBackground() {
        sf::Image gradient;
        gradient.create(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT, sf::Color::Transparent);
        
        for (int y = 0; y < Config::WINDOW_HEIGHT; ++y) {
            float t = static_cast<float>(y) / Config::WINDOW_HEIGHT;
            sf::Color color(
                static_cast<sf::Uint8>(60 + t * 20),
                static_cast<sf::Uint8>(45 + t * 30),
                static_cast<sf::Uint8>(80 + t * 40)
            );
            
            for (int x = 0; x < Config::WINDOW_WIDTH; ++x) {
                gradient.setPixel(x, y, color);
            }
        }
        
        backgroundTexture_.loadFromImage(gradient);
        backgroundSprite_.setTexture(backgroundTexture_);
    }
    
    void DifficultySelectState::initializeMenu() {
        menu_ = std::make_unique<Menu>(window_);
        menu_->setFont(font_);
        menu_->setTitle("SELECTION DE DIFFICULTE");
        // Slightly smaller text for the difficulty selection screen
        menu_->setTitleSize(36);
        menu_->setItemSize(24);
        menu_->setPosition(Config::WINDOW_WIDTH / 2.0f, 140);
        menu_->setSpacing(40);
        
        // Menu items
        menu_->addItem("DEBUTANT (9x9 - 10 mines)", [this]() {
            startGame(Config::Difficulty::BEGINNER, false);
        });
        
        menu_->addItem("INTERMEDIAIRE (16x16 - 40 mines)", [this]() {
            startGame(Config::Difficulty::INTERMEDIATE, false);
        });
        
        menu_->addItem("EXPERT (30x16 - 99 mines)", [this]() {
            startGame(Config::Difficulty::EXPERT, false);
        });
        
        menu_->addItem("RETOUR AU MENU", [this]() {
            stateManager_.popState();
        });
    }
    
    void DifficultySelectState::startGame(Config::Difficulty difficulty, bool timed) {
        // Créer une nouvelle partie - CORRECTION : passer stateManager_
        auto playingState = std::make_unique<PlayingState>(window_, stateManager_);
        stateManager_.changeState(std::move(playingState));
    }
    
    void DifficultySelectState::handleEvents(sf::RenderWindow& window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                // Handle only Escape here; delegate menu navigation/activation to Menu::handleEvent
                if (event.key.code == sf::Keyboard::Escape) {
                    stateManager_.popState();
                }
            }

            // Let the Menu class handle navigation keys (Up/Down/W/S), Enter, Space, etc.
            menu_->handleEvent(event);
        }
    }
    
    void DifficultySelectState::update(float deltaTime) {
        menu_->update();
    }
    
    void DifficultySelectState::render(sf::RenderWindow& window) {
        window.clear(sf::Color(Config::MENU_BACKGROUND_COLOR));
        window.draw(backgroundSprite_);
        menu_->render();
        
        // Info de difficulté
        auto settings = Config::getDifficultySettings(selectedDifficulty_);
        
        sf::Text infoText;
        infoText.setFont(font_);
        infoText.setString("Grille: " + std::to_string(settings.width) + "x" + 
                          std::to_string(settings.height) + 
                          " | Mines: " + std::to_string(settings.mines));
        
        infoText.setCharacterSize(18);
        infoText.setFillColor(sf::Color::Yellow);
        infoText.setStyle(sf::Text::Bold);
        
        sf::FloatRect bounds = infoText.getLocalBounds();
        infoText.setPosition((Config::WINDOW_WIDTH - bounds.width) / 2, 80);
        window.draw(infoText);
        
        // Contrôles
        sf::Text controlsText;
        controlsText.setFont(font_);
        controlsText.setString("ECHAP : Retour | ↑↓ : Navigation | ENTREE : Sélectionner");
        controlsText.setCharacterSize(12);
        controlsText.setFillColor(sf::Color(200, 200, 200, 150));
        controlsText.setPosition(10, Config::WINDOW_HEIGHT - 25);
        window.draw(controlsText);
    }
    
    void DifficultySelectState::onEnter() {
        std::cout << "Entering Difficulty Selection" << std::endl;
    }
    
    void DifficultySelectState::onExit() {
        std::cout << "Exiting Difficulty Selection" << std::endl;
    }
}