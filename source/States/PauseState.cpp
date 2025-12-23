#include "States/PauseState.hpp"
#include "States/MainMenuState.hpp"
#include "States/PlayingState.hpp"
#include "States/StateManager.hpp"
#include "Game/Config.hpp"
#include <iostream>
#include <cmath>

namespace Minesweeper {
    PauseState::PauseState(sf::RenderWindow& window, StateManager& stateManager) 
        : StateWithManager(window, stateManager) {  // CORRECTION ICI
        
        if (!font_.loadFromFile("assets/fonts/arial.ttf")) {
            std::cerr << "Failed to load font in PauseState" << std::endl;
            font_.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
        }
        
        overlay_.setSize(sf::Vector2f(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT));
        overlay_.setFillColor(sf::Color(0, 0, 0, 180));
         
        initializeMenu();
    }
    
    void PauseState::initializeMenu() {
        menu_ = std::make_unique<Menu>(window_);
        menu_->setFont(font_);
        menu_->setTitle("JEU EN PAUSE");
        // Slightly smaller title and item sizes for pause menu
        menu_->setTitleSize(36);
        menu_->setItemSize(20);

        // Align menu position with the menu background so items are inside the panel
        float menuBgY = (Config::WINDOW_HEIGHT - 400) / 3.0f;
        float menuY = menuBgY + 40.0f; // small top padding inside the background
        menu_->setPosition(Config::WINDOW_WIDTH / 2.0f, menuY);
        menu_->setSpacing(48);
        
        // Items du menu pause
        menu_->addItem("REPRENDRE LA PARTIE", [this]() {
            stateManager_.popState(); // Retour au jeu
        });
        
        menu_->addItem("RECOMMENCER", [this]() {
            // Créer une nouvelle partie avec les mêmes paramètres
            auto playingState = std::make_unique<PlayingState>(window_, stateManager_);
            stateManager_.changeState(std::move(playingState));
        });
        
        menu_->addItem("OPTIONS", [this]() {
            std::cout << "Options depuis le menu pause" << std::endl;
            // À implémenter
        });
        
        menu_->addItem("CHANGER DE DIFFICULTE", [this]() {
            std::cout << "Changement de difficulté depuis la pause" << std::endl;
            // À implémenter - retourner au menu de sélection
        });
        
        menu_->addItem("MENU PRINCIPAL", [this]() {
            auto mainMenu = std::make_unique<MainMenuState>(window_, stateManager_);
            stateManager_.changeState(std::move(mainMenu));
        });
        
        menu_->addItem("QUITTER LE JEU", [this]() {
            window_.close();
        });
    }
    
    void PauseState::handleEvents(sf::RenderWindow& window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                // Handle only pause-specific global keys here.
                if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::P) {
                    // Resume the game
                    stateManager_.popState();
                } else if (event.key.code == sf::Keyboard::R) {
                    // Shortcut to restart
                    auto playingState = std::make_unique<PlayingState>(window_, stateManager_);
                    stateManager_.changeState(std::move(playingState));
                }
                // Do not handle Enter/Up/Down here — delegate to Menu::handleEvent to avoid double handling
            }

            // Let the Menu handle navigation keys, Enter/Space and mouse events
            menu_->handleEvent(event);
        }
    }
    
    void PauseState::update(float deltaTime) {
        menu_->update();
        
        // Effet de pulsation pour le titre
        static float pulseTime = 0;
        pulseTime += deltaTime;
        float pulse = 0.7f + 0.3f * std::sin(pulseTime * 2.0f);
        
        // On pourrait animer l'overlay aussi
        sf::Uint8 alpha = static_cast<sf::Uint8>(160 + 20 * std::sin(pulseTime * 1.5f));
        overlay_.setFillColor(sf::Color(0, 0, 0, alpha));
    }
    
    void PauseState::render(sf::RenderWindow& window) {
        window.draw(overlay_);
        
        // Cadre pour le menu
        sf::RectangleShape menuBackground(sf::Vector2f(500, 400));
        menuBackground.setFillColor(sf::Color(30, 30, 46, 220));
        menuBackground.setOutlineThickness(3);
        menuBackground.setOutlineColor(sf::Color(70, 70, 100));
        menuBackground.setPosition((Config::WINDOW_WIDTH - 500) / 2, 
                                  (Config::WINDOW_HEIGHT - 400) / 3);
        window.draw(menuBackground);
                
        // Rendre le menu
        menu_->render();
        
        // Informations de contrôle
        sf::Text controlsText;
        controlsText.setFont(font_);
        controlsText.setString("Appuyez sur ECHAP ou P pour reprendre | R pour recommencer");
        controlsText.setCharacterSize(16);
        controlsText.setFillColor(sf::Color(200, 200, 200));
        controlsText.setStyle(sf::Text::Italic);
        
        sf::FloatRect ctrlBounds = controlsText.getLocalBounds();
        controlsText.setPosition((Config::WINDOW_WIDTH - ctrlBounds.width) / 2, 
                                Config::WINDOW_HEIGHT - 80);
        window.draw(controlsText);
        
        // Message d'aide
        sf::Text helpText;
        helpText.setFont(font_);
        helpText.setString("Votre progression est sauvegardee. Reprenez quand vous voulez !");
        helpText.setCharacterSize(12);
        helpText.setFillColor(sf::Color(150, 150, 180, 200));
        
        sf::FloatRect helpBounds = helpText.getLocalBounds();
        helpText.setPosition((Config::WINDOW_WIDTH - helpBounds.width) / 2, 
                            Config::WINDOW_HEIGHT - 50);
        window.draw(helpText);
        
        // Effet de bordure décorative
        sf::RectangleShape topBorder(sf::Vector2f(Config::WINDOW_WIDTH, 2));
        topBorder.setFillColor(sf::Color(100, 100, 150, 100));
        topBorder.setPosition(0, (Config::WINDOW_HEIGHT - 400) / 3 - 10);
        window.draw(topBorder);
        
        sf::RectangleShape bottomBorder(sf::Vector2f(Config::WINDOW_WIDTH, 2));
        bottomBorder.setFillColor(sf::Color(100, 100, 150, 100));
        bottomBorder.setPosition(0, (Config::WINDOW_HEIGHT - 400) / 3 + 410);
        window.draw(bottomBorder);
    }
    
    void PauseState::onEnter() {
        std::cout << "=== ENTREE MENU PAUSE ===" << std::endl;
        std::cout << "Jeu mis en pause" << std::endl;
        std::cout << "Options disponibles:" << std::endl;
        std::cout << "  - Reprendre (ECHAP/P)" << std::endl;
        std::cout << "  - Recommencer (R)" << std::endl;
        std::cout << "  - Retour au menu principal" << std::endl;
        std::cout << "  - Quitter le jeu" << std::endl;
    }
    
    void PauseState::onExit() {
        std::cout << "=== SORTIE MENU PAUSE ===" << std::endl;
        std::cout << "Reprise du jeu..." << std::endl;
    }
}