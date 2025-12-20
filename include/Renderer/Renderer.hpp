#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../Game/Config.hpp"
#include "../Logic/GameLogic.hpp"
#include "AssetManager.hpp"

namespace Minesweeper {
    class Renderer {
    public:
        Renderer(std::shared_ptr<GameLogic> gameLogic, 
                std::shared_ptr<AssetManager> assetManager);
        
        // Rendering
        void render(sf::RenderWindow& window);
        
        // UI Helpers
        sf::Vector2i screenToBoardPosition(int screenX, int screenY) const;
        
    private:
        std::shared_ptr<GameLogic> gameLogic_;
        std::shared_ptr<AssetManager> assetManager_;
        
        // Rendering methods
        void renderBoard(sf::RenderWindow& window);
        void renderUI(sf::RenderWindow& window);
        void renderCell(sf::RenderWindow& window, int x, int y);
        void renderMineCounter(sf::RenderWindow& window);
        void renderTimer(sf::RenderWindow& window);
        void renderFaceButton(sf::RenderWindow& window);
        void renderGameStatus(sf::RenderWindow& window);  // Nouvelle méthode
        
        // Helper methods
        void drawDigit(sf::RenderWindow& window, int digit, int x, int y);
        void drawNumber(sf::RenderWindow& window, int number, int x, int y, int digitCount = 3);
    };
}