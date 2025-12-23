#pragma once
#include "StateWithManager.hpp"
#include "../Logic/GameLogic.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Renderer/AssetManager.hpp"
#include "../Input/InputHandler.hpp"
#include "../UI/UIManager.hpp"
#include <memory>

namespace Minesweeper {
    class PlayingState : public StateWithManager {
    public:
        PlayingState(sf::RenderWindow& window, StateManager& stateManager);
        
        void handleEvents(sf::RenderWindow& window) override;
        void update(float deltaTime) override;
        void render(sf::RenderWindow& window) override;
        
        void onEnter() override;
        void onExit() override;
        
    private:
        std::shared_ptr<GameLogic> gameLogic_;
        std::shared_ptr<AssetManager> assetManager_;
        std::shared_ptr<Renderer> renderer_;
        std::shared_ptr<InputHandler> inputHandler_;
        std::shared_ptr<UIManager> uiManager_;
        
        void initialize();
    };
}