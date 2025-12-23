#pragma once
#include "StateWithManager.hpp"
#include "../UI/Menu.hpp"
#include "../Game/Config.hpp"
#include <memory>

namespace Minesweeper {
    class DifficultySelectState : public StateWithManager {
    public:
        DifficultySelectState(sf::RenderWindow& window, StateManager& stateManager);
        
        void handleEvents(sf::RenderWindow& window) override;
        void update(float deltaTime) override;
        void render(sf::RenderWindow& window) override;
        
        void onEnter() override;
        void onExit() override;
        
    private:
        std::unique_ptr<Menu> menu_;
        sf::Font font_;
        sf::Texture backgroundTexture_;
        sf::Sprite backgroundSprite_;
        
        Config::Difficulty selectedDifficulty_ = Config::Difficulty::INTERMEDIATE;
        
        void initializeMenu();
        void createBackground();
        void startGame(Config::Difficulty difficulty, bool timed);
    };
}