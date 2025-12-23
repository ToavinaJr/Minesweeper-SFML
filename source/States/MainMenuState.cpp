#include "States/MainMenuState.hpp"
#include "States/DifficultySelectState.hpp"
#include "States/PlayingState.hpp"
#include "States/HelpState.hpp"
#include "Game/Config.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

namespace Minesweeper {
    MainMenuState::MainMenuState(sf::RenderWindow& window, StateManager& stateManager) 
        : StateWithManager(window, stateManager) {
        
        // Initialiser le générateur aléatoire
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        
        // Load font
        if (!font_.loadFromFile("assets/fonts/arial.ttf")) {
            std::cerr << "Failed to load font in MainMenuState" << std::endl;
            // Créer une police par défaut si échec
            font_.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf");
        }
        
        createBackground();
        initializeMenu();
    }
    
    void MainMenuState::createBackground() {
        // Créer un fond avec dégradé
        sf::Image gradient;
        gradient.create(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT, sf::Color::Transparent);
        
        // Créer un dégradé bleu foncé -> violet
        for (int y = 0; y < Config::WINDOW_HEIGHT; ++y) {
            float t = static_cast<float>(y) / Config::WINDOW_HEIGHT;
            sf::Color color(
                static_cast<sf::Uint8>(30 + t * 40),   // R
                static_cast<sf::Uint8>(30 + t * 30),   // G
                static_cast<sf::Uint8>(46 + t * 60)    // B
            );
            
            for (int x = 0; x < Config::WINDOW_WIDTH; ++x) {
                gradient.setPixel(x, y, color);
            }
        }
        
        backgroundTexture_.loadFromImage(gradient);
        backgroundSprite_.setTexture(backgroundTexture_);
        
        // Ajouter des motifs de mines en arrière-plan
        sf::RenderTexture patternTexture;
        patternTexture.create(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT);
        patternTexture.clear(sf::Color::Transparent);
        
        // Dessiner des mines décoratives
        for (int i = 0; i < 15; ++i) {
            float x = static_cast<float>(std::rand() % Config::WINDOW_WIDTH);
            float y = static_cast<float>(std::rand() % Config::WINDOW_HEIGHT);
            float radius = 3.0f + static_cast<float>(std::rand() % 10);
            
            sf::CircleShape minePattern(radius);
            minePattern.setPosition(x, y);
            minePattern.setFillColor(sf::Color(255, 255, 255, 30));
            patternTexture.draw(minePattern);
            
            // Ajouter des "rayons" pour certaines mines
            if (i % 3 == 0) {
                for (int j = 0; j < 8; ++j) {
                    float angle = j * 45.0f * 3.14159f / 180.0f;
                    float x2 = x + radius + cos(angle) * (radius * 2);
                    float y2 = y + radius + sin(angle) * (radius * 2);
                    
                    sf::Vertex line[] = {
                        sf::Vertex(sf::Vector2f(x + radius, y + radius), sf::Color(255, 255, 255, 20)),
                        sf::Vertex(sf::Vector2f(x2, y2), sf::Color(255, 255, 255, 20))
                    };
                    patternTexture.draw(line, 2, sf::Lines);
                }
            }
        }
        
        patternTexture.display();
        sf::Sprite patternSprite(patternTexture.getTexture());
        
        // Combiner avec le fond
        sf::RenderTexture finalTexture;
        finalTexture.create(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT);
        finalTexture.draw(backgroundSprite_);
        finalTexture.draw(patternSprite);
        finalTexture.display();
        
        backgroundTexture_ = finalTexture.getTexture();
        backgroundSprite_.setTexture(backgroundTexture_);
    }
    
    void MainMenuState::initializeMenu() {
        menu_ = std::make_unique<Menu>(window_);
        
        menu_->setFont(font_);
        menu_->setTitle("MINESWEEPER");
        menu_->setPosition(Config::WINDOW_WIDTH / 2.0f, 120);
        menu_->setSpacing(55);
        
        // Items du menu
        menu_->addItem("NOUVELLE PARTIE", [this]() {
            // Aller à la sélection de difficulté
            auto difficultyState = std::make_unique<DifficultySelectState>(window_, stateManager_);
            stateManager_.pushState(std::move(difficultyState));
        });
        
        menu_->addItem("PARTIE RAPIDE", [this]() {
            // Démarrer directement une partie intermédiaire
            auto playingState = std::make_unique<PlayingState>(window_, stateManager_);
            stateManager_.changeState(std::move(playingState));
        });
        
        menu_->addItem("OPTIONS", [this]() {
            std::cout << "Options menu selected" << std::endl;
            // À implémenter plus tard
        });
        
        menu_->addItem("COMMENT JOUER", [this]() {
            auto help = std::make_unique<HelpState>(window_, stateManager_);
            stateManager_.pushState(std::move(help));
        });
        
        menu_->addItem("QUITTER", [this]() {
            window_.close();
        });
    }
    
    void MainMenuState::handleEvents(sf::RenderWindow& window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                // Only handle global keys here (Escape to quit). Menu handles navigation and activation.
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
            
            menu_->handleEvent(event);
        }
    }
    
    void MainMenuState::update(float deltaTime) {
        menu_->update();
        
        // Animation subtile du fond
        static float time = 0;
        time += deltaTime;
        
        // Légère variation de luminosité
        float pulse = 0.5f + 0.5f * sin(time * 0.5f);
        backgroundSprite_.setColor(sf::Color(255, 255, 255, 
            static_cast<sf::Uint8>(200 + 55 * pulse)));
    }
    
    void MainMenuState::render(sf::RenderWindow& window) {
        window.clear(sf::Color(Config::MENU_BACKGROUND_COLOR));
        window.draw(backgroundSprite_);
        menu_->render();
        
        // Informations de version
        sf::Text versionText;
        versionText.setFont(font_);
        versionText.setString("Version 2.0 | Developpe avec SFML");
        versionText.setCharacterSize(14);
        versionText.setFillColor(sf::Color(180, 180, 220, 180));
        versionText.setStyle(sf::Text::Italic);
        versionText.setPosition(10, Config::WINDOW_HEIGHT - 25);
        window.draw(versionText);
        
        // Contrôles
        sf::Text controlsText;
        controlsText.setFont(font_);
        controlsText.setString("UP/DOWN ou WASD : Navigation | ENTREE : Selectionner | ECHAP : Quitter");
        controlsText.setCharacterSize(14);
        controlsText.setFillColor(sf::Color(200, 200, 200, 180));
        
        sf::FloatRect bounds = controlsText.getLocalBounds();
        controlsText.setPosition((Config::WINDOW_WIDTH - bounds.width) / 2, 
                                Config::WINDOW_HEIGHT - 45);
        window.draw(controlsText);
        
        // Crédits
        sf::Text creditsText;
        creditsText.setFont(font_);
        creditsText.setString("Un classique revisite - Amusez-vous !");
        creditsText.setCharacterSize(16);
        creditsText.setFillColor(sf::Color(255, 215, 0, 200)); // Or
        creditsText.setStyle(sf::Text::Bold);
        
        sf::FloatRect creditsBounds = creditsText.getLocalBounds();
        creditsText.setPosition((Config::WINDOW_WIDTH - creditsBounds.width) / 2, 
                               Config::WINDOW_HEIGHT - 80);
        window.draw(creditsText);
        
        // Afficher les statistiques du dernier jeu (si disponibles)
        sf::Text statsText;
        statsText.setFont(font_);
        statsText.setString("Derniere partie: 16x16 - 40 mines - Meilleur temps: --:--");
        statsText.setCharacterSize(12);
        statsText.setPosition(Config::WINDOW_WIDTH - 320, 10);
        window.draw(statsText);
    }
    
    void MainMenuState::onEnter() {
        std::cout << "=== ENTREE MENU PRINCIPAL ===" << std::endl;
        std::cout << "Sélectionnez une option avec les flèches ou WASD" << std::endl;
        std::cout << "Appuyez sur ENTREE pour valider" << std::endl;
        std::cout << "Appuyez sur ECHAP pour quitter" << std::endl;
    }
    
    void MainMenuState::onExit() {
        std::cout << "=== SORTIE MENU PRINCIPAL ===" << std::endl;
    }
}