#include "Renderer/AssetManager.hpp"
#include <iostream>
#include <cmath>

namespace Minesweeper {
    AssetManager::AssetManager() {
    }

    bool AssetManager::loadAssets() {
        loadFont();
        generateTileTextures();
        generateFaceTextures();
        generateDigitTextures();
        
        return true;
    }

    void AssetManager::generateTileTextures() {
        // Generate basic tile textures
        generatedTextures_["tile_hidden"] = createHiddenTileTexture();
        generatedTextures_["tile_revealed"] = createRevealedTileTexture();
        generatedTextures_["mine"] = createMineTexture();
        generatedTextures_["flag"] = createFlagTexture();
        
        // Generate number textures
        for (int i = 1; i <= 8; ++i) {
            generatedTextures_["number_" + std::to_string(i)] = createNumberTexture(i);
        }
        
        // Generate digit textures for counters
        for (int i = 0; i <= 9; ++i) {
            generatedTextures_["digit_" + std::to_string(i)] = createDigitTexture(i);
        }
    }

    void AssetManager::generateFaceTextures() {
        generatedTextures_["face_happy"] = createFaceTexture("happy");
        generatedTextures_["face_win"] = createFaceTexture("win");
        generatedTextures_["face_lose"] = createFaceTexture("lose");
    }

    void AssetManager::generateDigitTextures() {
        // Already generated in generateTileTextures
    }

    void AssetManager::loadFont() {
        if (!font_.loadFromFile("assets/fonts/arial.ttf")) {
            // Try system font as fallback
            if (!font_.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf")) {
                std::cerr << "Failed to load font" << std::endl;
            }
        }
    }

    const sf::Texture& AssetManager::getTileTexture(bool hidden, bool flagged, 
                                                   bool revealed, bool hasMine, 
                                                   int adjacentMines) {
        if (hidden && !revealed) {
            if (flagged) {
                return generatedTextures_["flag"];
            }
            return generatedTextures_["tile_hidden"];
        }
        
        if (revealed) {
            if (hasMine) {
                return generatedTextures_["mine"];
            }
            
            if (adjacentMines > 0) {
                return generatedTextures_["number_" + std::to_string(adjacentMines)];
            }
            
            return generatedTextures_["tile_revealed"];
        }
        
        // Default fallback
        return generatedTextures_["tile_hidden"];
    }

    const sf::Texture& AssetManager::getFaceTexture(Config::GameState state) {
        switch (state) {
            case Config::GameState::WON:
                return generatedTextures_["face_win"];
            case Config::GameState::LOST:
                return generatedTextures_["face_lose"];
            case Config::GameState::PLAYING:
            default:
                return generatedTextures_["face_happy"];
        }
    }

    sf::Color AssetManager::getNumberColor(int number) const {
        switch (number) {
            case 1: return sf::Color::Blue;
            case 2: return sf::Color(0, 150, 0); // Dark Green
            case 3: return sf::Color::Red;
            case 4: return sf::Color(0, 0, 128); // Navy
            case 5: return sf::Color(128, 0, 0); // Maroon
            case 6: return sf::Color(64, 224, 208); // Turquoise
            case 7: return sf::Color::Black;
            case 8: return sf::Color(128, 128, 128); // Gray
            default: return sf::Color::Black;
        }
    }

    sf::Texture AssetManager::createHiddenTileTexture() {
        int size = Config::TILE_SIZE;
        sf::RenderTexture renderTexture;
        renderTexture.create(size, size);
        
        // Clear with gray color
        renderTexture.clear(sf::Color(192, 192, 192));
        
        // Draw 3D effect
        sf::RectangleShape topBorder(sf::Vector2f(size, 2));
        topBorder.setFillColor(sf::Color(255, 255, 255));
        renderTexture.draw(topBorder);
        
        sf::RectangleShape leftBorder(sf::Vector2f(2, size));
        leftBorder.setFillColor(sf::Color(255, 255, 255));
        renderTexture.draw(leftBorder);
        
        sf::RectangleShape bottomBorder(sf::Vector2f(size, 2));
        bottomBorder.setPosition(0, size - 2);
        bottomBorder.setFillColor(sf::Color(128, 128, 128));
        renderTexture.draw(bottomBorder);
        
        sf::RectangleShape rightBorder(sf::Vector2f(2, size));
        rightBorder.setPosition(size - 2, 0);
        rightBorder.setFillColor(sf::Color(128, 128, 128));
        renderTexture.draw(rightBorder);
        
        // Draw inner bevel
        sf::RectangleShape innerBevel(sf::Vector2f(size - 4, size - 4));
        innerBevel.setPosition(2, 2);
        innerBevel.setFillColor(sf::Color(192, 192, 192));
        renderTexture.draw(innerBevel);
        
        renderTexture.display();
        return renderTexture.getTexture();
    }

    sf::Texture AssetManager::createRevealedTileTexture() {
        int size = Config::TILE_SIZE;
        sf::RenderTexture renderTexture;
        renderTexture.create(size, size);
        
        // Clear with light gray color
        renderTexture.clear(sf::Color(220, 220, 220));
        
        // Draw subtle border
        sf::RectangleShape border(sf::Vector2f(size - 2, size - 2));
        border.setPosition(1, 1);
        border.setFillColor(sf::Color::Transparent);
        border.setOutlineColor(sf::Color(180, 180, 180));
        border.setOutlineThickness(1);
        renderTexture.draw(border);
        
        renderTexture.display();
        return renderTexture.getTexture();
    }

    sf::Texture AssetManager::createMineTexture() {
        int size = Config::TILE_SIZE;
        int center = size / 2;
        sf::RenderTexture renderTexture;
        renderTexture.create(size, size);
        
        // Clear with revealed tile color
        renderTexture.clear(sf::Color(220, 220, 220));
        
        // Draw mine (black circle with spikes)
        sf::CircleShape mineBody(center - 4);
        mineBody.setFillColor(sf::Color::Black);
        mineBody.setPosition(4, 4);
        renderTexture.draw(mineBody);
        
        // Draw spikes
        for (int i = 0; i < 8; ++i) {
            float angle = i * 45.0f * 3.14159f / 180.0f;
            float x1 = center + cos(angle) * (center - 8);
            float y1 = center + sin(angle) * (center - 8);
            float x2 = center + cos(angle) * (center + 2);
            float y2 = center + sin(angle) * (center + 2);
            
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x1, y1), sf::Color::Black),
                sf::Vertex(sf::Vector2f(x2, y2), sf::Color::Black)
            };
            renderTexture.draw(line, 2, sf::Lines);
        }
        
        // Draw highlight
        sf::CircleShape highlight(center - 8);
        highlight.setFillColor(sf::Color(100, 100, 100));
        highlight.setPosition(8, 8);
        renderTexture.draw(highlight);
        
        renderTexture.display();
        return renderTexture.getTexture();
    }

    sf::Texture AssetManager::createFlagTexture() {
        int size = Config::TILE_SIZE;
        int center = size / 2;
        sf::RenderTexture renderTexture;
        renderTexture.create(size, size);
        
        // Start with hidden tile
        renderTexture.clear(sf::Color(192, 192, 192));
        
        // Draw flag pole
        sf::RectangleShape pole(sf::Vector2f(2, size - 8));
        pole.setFillColor(sf::Color::Black);
        pole.setPosition(center - 1, 4);
        renderTexture.draw(pole);
        
        // Draw flag (red triangle)
        sf::ConvexShape flag;
        flag.setPointCount(3);
        flag.setPoint(0, sf::Vector2f(center + 1, 8));
        flag.setPoint(1, sf::Vector2f(center + 1, size / 2));
        flag.setPoint(2, sf::Vector2f(size - 4, center - 4));
        flag.setFillColor(sf::Color::Red);
        renderTexture.draw(flag);
        
        renderTexture.display();
        return renderTexture.getTexture();
    }

    sf::Texture AssetManager::createNumberTexture(int number) {
        int size = Config::TILE_SIZE;
        sf::RenderTexture renderTexture;
        renderTexture.create(size, size);
        
        // Clear with revealed tile color
        renderTexture.clear(sf::Color(220, 220, 220));
        
        if (font_.getInfo().family != "") {
            // Draw number
            sf::Text numberText;
            numberText.setFont(font_);
            numberText.setString(std::to_string(number));
            numberText.setCharacterSize(size - 12);
            numberText.setFillColor(getNumberColor(number));
            
            // Center the text
            sf::FloatRect textBounds = numberText.getLocalBounds();
            numberText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                               textBounds.top + textBounds.height / 2.0f);
            numberText.setPosition(size / 2.0f, size / 2.0f);
            
            renderTexture.draw(numberText);
        }
        
        renderTexture.display();
        return renderTexture.getTexture();
    }

    sf::Texture AssetManager::createFaceTexture(const std::string& faceType) {
        sf::RenderTexture renderTexture;
        renderTexture.create(60, 60); // Taille augmentée à 60x60
        
        // Clear with yellow background
        sf::Color faceColor = sf::Color::Yellow;
        if (faceType == "win") {
            faceColor = sf::Color::Green;
        } else if (faceType == "lose") {
            faceColor = sf::Color::Red;
        }
        
        renderTexture.clear(faceColor);
        
        // Draw face outline
        sf::CircleShape face(25); // Rayon augmenté
        face.setFillColor(sf::Color(255, 255, 200));
        face.setPosition(5, 5);
        face.setOutlineThickness(2);
        face.setOutlineColor(sf::Color::Black);
        renderTexture.draw(face);
        
        // Draw eyes
        sf::CircleShape leftEye(5); // Yeux plus grands
        leftEye.setFillColor(sf::Color::Black);
        leftEye.setPosition(18, 20);
        renderTexture.draw(leftEye);
        
        sf::CircleShape rightEye(5); // Yeux plus grands
        rightEye.setFillColor(sf::Color::Black);
        rightEye.setPosition(38, 20);
        renderTexture.draw(rightEye);
        
        // Draw mouth
        if (faceType == "happy") {
            // Smile
            sf::CircleShape mouth(12, 20);
            mouth.setFillColor(sf::Color::Transparent);
            mouth.setOutlineThickness(2);
            mouth.setOutlineColor(sf::Color::Black);
            mouth.setPosition(18, 28);
            mouth.setScale(1.0f, 0.5f);
            renderTexture.draw(mouth);
        } else if (faceType == "win") {
            // Big smile
            sf::CircleShape mouth(14, 20);
            mouth.setFillColor(sf::Color::Transparent);
            mouth.setOutlineThickness(2);
            mouth.setOutlineColor(sf::Color::Black);
            mouth.setPosition(16, 26);
            mouth.setScale(1.0f, 0.6f);
            renderTexture.draw(mouth);
        } else if (faceType == "lose") {
            // Sad face
            sf::VertexArray mouth(sf::LinesStrip, 3);
            mouth[0].position = sf::Vector2f(18, 40);
            mouth[0].color = sf::Color::Black;
            mouth[1].position = sf::Vector2f(30, 44);
            mouth[1].color = sf::Color::Black;
            mouth[2].position = sf::Vector2f(42, 40);
            mouth[2].color = sf::Color::Black;
            renderTexture.draw(mouth);
        }
        
        renderTexture.display();
        return renderTexture.getTexture();
    }

    sf::Texture AssetManager::createDigitTexture(int digit) {
        sf::RenderTexture renderTexture;
        renderTexture.create(24, 48); // Larger for counter display
        
        // Clear with dark background
        renderTexture.clear(sf::Color::Black);
        
        if (font_.getInfo().family != "") {
            // Draw digit
            sf::Text digitText;
            digitText.setFont(font_);
            digitText.setString(std::to_string(digit));
            digitText.setCharacterSize(36);
            digitText.setFillColor(sf::Color::Red);
            
            // Center the text
            sf::FloatRect textBounds = digitText.getLocalBounds();
            digitText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                              textBounds.top + textBounds.height / 2.0f);
            digitText.setPosition(12, 24);
            
            renderTexture.draw(digitText);
        }
        
        renderTexture.display();
        return renderTexture.getTexture();
    }
}