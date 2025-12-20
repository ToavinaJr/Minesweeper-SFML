#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Button.hpp"
#include "../Logic/GameLogic.hpp"
#include "../Renderer/AssetManager.hpp"

namespace Minesweeper {
    class UIManager {
    public:
        UIManager(std::shared_ptr<GameLogic> gameLogic,
                  std::shared_ptr<AssetManager> assetManager);
        
        void update(float deltaTime);
        void render(sf::RenderWindow& window);
        void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
        
        // UI Elements
        bool isFaceButtonClicked(const sf::Vector2i& mousePos) const;
        
    private:
        std::shared_ptr<GameLogic> gameLogic_;
        std::shared_ptr<AssetManager> assetManager_;
        
        sf::RectangleShape uiPanel_;
        Button newGameButton_;
        
        void setupUI();
        void renderGameInfo(sf::RenderWindow& window);
        void renderFaceButton(sf::RenderWindow& window);
    };
}
