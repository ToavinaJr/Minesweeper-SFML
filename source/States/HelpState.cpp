#include "States/HelpState.hpp"
#include "States/StateManager.hpp"
#include "Game/Config.hpp"
#include <iostream>

namespace Minesweeper {
    HelpState::HelpState(sf::RenderWindow& window, StateManager& stateManager)
        : StateWithManager(window, stateManager) {
        if (!font_.loadFromFile("assets/fonts/arial.ttf")) {
            std::cerr << "Failed to load font in HelpState" << std::endl;
            font_.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
        }

        createHelpText();
        initializeMenu();
    }

    void HelpState::createHelpText() {
        helpText_.setFont(font_);
        helpText_.setString("But:\nTrouver toutes les mines \nUtilisez le clic gauche pour rEvEler une case, \nle clic droit pour marquer une mine.\n\nConseils:\n- Commencez par rEvEler les coins.\n- Utilisez les chiffres pour dEduire \noU se trouvent les mines.\n- Faites attention aux drapeaux.\n");
        helpText_.setCharacterSize(18);
        helpText_.setFillColor(sf::Color(220,220,220));
    }

    void HelpState::initializeMenu() {
        menu_ = std::make_unique<Menu>(window_);
        menu_->setFont(font_);
        menu_->setTitle("COMMENT JOUER");
        menu_->setTitleSize(36);
        menu_->setItemSize(20);
        menu_->setPosition(Config::WINDOW_WIDTH / 2.0f, 120);
        menu_->setSpacing(44);

        menu_->addItem("RETOUR", [this]() {
            stateManager_.popState();
        });
    }

    void HelpState::handleEvents(sf::RenderWindow& window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    stateManager_.popState();
                }
            }

            menu_->handleEvent(event);
        }
    }

    void HelpState::update(float deltaTime) {
        menu_->update();
    }

    void HelpState::render(sf::RenderWindow& window) {
        window.clear(sf::Color(Config::MENU_BACKGROUND_COLOR));
        menu_->render();

        // Draw help text below title
        sf::FloatRect tb = helpText_.getLocalBounds();
        helpText_.setOrigin(tb.left, tb.top);
        helpText_.setPosition(60, 220);
        window.draw(helpText_);
    }

    void HelpState::onEnter() {
        std::cout << "Entering Help State" << std::endl;
    }

    void HelpState::onExit() {
        std::cout << "Exiting Help State" << std::endl;
    }
}
