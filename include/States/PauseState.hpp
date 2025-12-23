#pragma once
#include "StateWithManager.hpp"
#include "../UI/Menu.hpp"
#include <memory>

namespace Minesweeper {
    class PauseState : public StateWithManager {
    public:
        PauseState(sf::RenderWindow& window, StateManager& stateManager);
        
        void handleEvents(sf::RenderWindow& window) override;
        void update(float deltaTime) override;
        void render(sf::RenderWindow& window) override;
        
        void onEnter() override;
        void onExit() override;
        
    private:
        std::unique_ptr<Menu> menu_;
        sf::Font font_;
        sf::RectangleShape overlay_;
        
        void initializeMenu();
    };
}