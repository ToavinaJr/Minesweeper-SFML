#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include "../Game/Config.hpp"

namespace Minesweeper {
    class AssetManager {
    public:
        AssetManager();
        
        // Asset loading
        bool loadAssets();
        
        // Resource access
        const sf::Texture& getTileTexture(bool hidden, bool flagged, bool revealed, bool hasMine, int adjacentMines);
        const sf::Texture& getFaceTexture(Config::GameState state);
        const sf::Font& getFont() const { return font_; }
        
        // Get color for numbers
        sf::Color getNumberColor(int number) const;
        
    private:
        sf::Font font_;
        
        // Generated textures
        std::map<std::string, sf::Texture> generatedTextures_;
        
        void generateTileTextures();
        void generateFaceTextures();
        void generateDigitTextures();
        void loadFont();
        
        // Helper methods
        sf::Texture createHiddenTileTexture();
        sf::Texture createRevealedTileTexture();
        sf::Texture createMineTexture();
        sf::Texture createFlagTexture();
        sf::Texture createNumberTexture(int number);
        sf::Texture createFaceTexture(const std::string& faceType);
        sf::Texture createDigitTexture(int digit);
    };
}