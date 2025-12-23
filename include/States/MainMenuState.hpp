#pragma once
#include "StateWithManager.hpp"
#include "../UI/Menu.hpp"
#include <memory>

namespace Minesweeper {
    class MainMenuState : public StateWithManager {
    public:
        MainMenuState(sf::RenderWindow& window, StateManager& stateManager);
        
        void handleEvents(sf::RenderWindow& window) override;
        void update(float deltaTime) override;
        void render(sf::RenderWindow& window) override;
        
        void onEnter() override;
        void onExit() override;
        
    private:
        std::unique_ptr<Menu> menu_;
        sf::Texture backgroundTexture_;
        sf::Sprite backgroundSprite_;
        sf::Font font_;
        
        void initializeMenu();
        void createBackground();
    };
}