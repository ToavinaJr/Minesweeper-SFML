#include "Renderer/Renderer.hpp"
#include <algorithm>
#include <iostream>

namespace Minesweeper {
    Renderer::Renderer(std::shared_ptr<GameLogic> gameLogic,
                      std::shared_ptr<AssetManager> assetManager)
        : gameLogic_(gameLogic), assetManager_(assetManager) {
    }

    void Renderer::render(sf::RenderWindow& window) {
        renderBoard(window);
        renderUI(window);
    }

    void Renderer::renderBoard(sf::RenderWindow& window) {
        if (!gameLogic_ || !assetManager_) return;
        
        auto board = gameLogic_->getBoard();
        if (!board) return;
        
        for (int y = 0; y < board->getHeight(); ++y) {
            for (int x = 0; x < board->getWidth(); ++x) {
                renderCell(window, x, y);
            }
        }
    }

    void Renderer::renderCell(sf::RenderWindow& window, int x, int y) {
        if (!gameLogic_ || !assetManager_) return;
        
        auto board = gameLogic_->getBoard();
        if (!board) return;
        
        const Cell& cell = board->getCell(x, y);
        
        // Get the appropriate texture
        const sf::Texture& texture = assetManager_->getTileTexture(
            !cell.isRevealed(),
            cell.isFlagged(),
            cell.isRevealed(),
            cell.hasMine(),
            cell.getAdjacentMines()
        );
        
        // Create sprite
        sf::Sprite sprite(texture);
        sprite.setPosition(x * Config::TILE_SIZE, 
                          y * Config::TILE_SIZE + Config::UI_HEIGHT);
        
        // Scale if needed
        sf::Vector2u texSize = texture.getSize();
        if (texSize.x != Config::TILE_SIZE || texSize.y != Config::TILE_SIZE) {
            sprite.setScale(
                Config::TILE_SIZE / static_cast<float>(texSize.x),
                Config::TILE_SIZE / static_cast<float>(texSize.y)
            );
        }
        
        window.draw(sprite);
        
        // If the cell is revealed and has a mine, draw an explosion effect when game is lost
        if (cell.isRevealed() && cell.hasMine() && gameLogic_->isGameOver()) {
            // Draw a red circle over the mine to indicate explosion
            sf::CircleShape explosion(Config::TILE_SIZE / 2);
            explosion.setFillColor(sf::Color(255, 0, 0, 100)); // Semi-transparent red
            explosion.setPosition(x * Config::TILE_SIZE, 
                                 y * Config::TILE_SIZE + Config::UI_HEIGHT);
            window.draw(explosion);
        }
    }

    void Renderer::renderUI(sf::RenderWindow& window) {
        // Draw UI background
        sf::RectangleShape uiBackground(sf::Vector2f(Config::WINDOW_WIDTH, Config::UI_HEIGHT));
        uiBackground.setFillColor(sf::Color(Config::UI_BACKGROUND_COLOR));
        window.draw(uiBackground);
        
        // Draw UI elements
        renderMineCounter(window);
        renderTimer(window);
        renderFaceButton(window);
        
        // Draw game status text
        renderGameStatus(window);
    }

    void Renderer::renderMineCounter(sf::RenderWindow& window) {
        if (!gameLogic_ || !assetManager_) return;
        
        auto board = gameLogic_->getBoard();
        if (!board) return;
        
        int minesLeft = board->getMineCount() - board->getFlagCount();
        minesLeft = std::max(0, minesLeft); // Ensure non-negative
        
        // Create a background panel for the counter
        sf::RectangleShape counterBackground(sf::Vector2f(140, 50)); // Augmenté la taille
        counterBackground.setFillColor(sf::Color::Black);
        counterBackground.setPosition(30, 30); // Ajusté la position verticale
        counterBackground.setOutlineThickness(2);
        counterBackground.setOutlineColor(sf::Color::White);
        window.draw(counterBackground);
        
        // Draw counter using text
        sf::Text counterText;
        counterText.setFont(assetManager_->getFont());
        counterText.setString(std::to_string(minesLeft));
        counterText.setCharacterSize(32); // Taille augmentée
        counterText.setFillColor(sf::Color::Red);
        counterText.setStyle(sf::Text::Bold);
        
        // Center text in the panel
        sf::FloatRect textBounds = counterText.getLocalBounds();
        counterText.setPosition(
            30 + (140 - textBounds.width) / 2 - textBounds.left,
            25 + (50 - textBounds.height) / 2 - textBounds.top
        );
        
        window.draw(counterText);
        
        // Draw label above counter
        sf::Text labelText;
        labelText.setFont(assetManager_->getFont());
        labelText.setString("MINES LEFT");
        labelText.setCharacterSize(16);
        labelText.setFillColor(sf::Color::White);
        labelText.setPosition(30, 5);
        window.draw(labelText);
    }

    void Renderer::renderTimer(sf::RenderWindow& window) {
        if (!gameLogic_ || !assetManager_) return;
        
        int gameTime = gameLogic_->getGameTime();
        
        // Create a background panel for the timer
        sf::RectangleShape timerBackground(sf::Vector2f(140, 50)); // Augmenté la taille
        timerBackground.setFillColor(sf::Color::Black);
        timerBackground.setPosition(Config::WINDOW_WIDTH - 170, 30); // Ajusté la position
        timerBackground.setOutlineThickness(2);
        timerBackground.setOutlineColor(sf::Color::White);
        window.draw(timerBackground);
        
        // Draw timer using text
        sf::Text timerText;
        timerText.setFont(assetManager_->getFont());
        timerText.setString(std::to_string(gameTime));
        timerText.setCharacterSize(32); // Taille augmentée
        timerText.setFillColor(sf::Color::Red);
        timerText.setStyle(sf::Text::Bold);
        
        // Center text in the panel
        sf::FloatRect textBounds = timerText.getLocalBounds();
        timerText.setPosition(
            Config::WINDOW_WIDTH - 170 + (140 - textBounds.width) / 2 - textBounds.left,
            25 + (50 - textBounds.height) / 2 - textBounds.top
        );
        
        window.draw(timerText);
        
        // Draw label above timer
        sf::Text labelText;
        labelText.setFont(assetManager_->getFont());
        labelText.setString("TIME");
        labelText.setCharacterSize(16);
        labelText.setFillColor(sf::Color::White);
        labelText.setPosition(Config::WINDOW_WIDTH - 170, 5);
        window.draw(labelText);
    }

    void Renderer::renderFaceButton(sf::RenderWindow& window) {
        if (!gameLogic_ || !assetManager_) return;
        
        Config::GameState state = gameLogic_->getGameState();
        const sf::Texture& faceTexture = assetManager_->getFaceTexture(state);
        
        sf::Sprite faceSprite(faceTexture);
        
        // Center the face button - position ajustée
        float x = (Config::WINDOW_WIDTH - 70) / 2.0f;
        float y = (Config::UI_HEIGHT - 70) / 2.0f + 10; // Décalé vers le bas
        
        // Draw button background
        sf::RectangleShape buttonBackground(sf::Vector2f(70, 70)); // Bouton plus grand
        buttonBackground.setFillColor(sf::Color(50, 50, 70));
        buttonBackground.setPosition(x, y);
        buttonBackground.setOutlineThickness(3); // Bordure plus épaisse
        buttonBackground.setOutlineColor(sf::Color::White);
        window.draw(buttonBackground);
        
        // Position and draw face sprite
        faceSprite.setPosition(x + 10, y + 10); // Marge interne
        
        // Scale to fit in button
        sf::Vector2u texSize = faceTexture.getSize();
        if (texSize.x != 50 || texSize.y != 50) {
            faceSprite.setScale(50.0f / texSize.x, 50.0f / texSize.y);
        }
        
        window.draw(faceSprite);
    }

    void Renderer::renderGameStatus(sf::RenderWindow& window) {
        if (!gameLogic_ || !assetManager_) return;
        
        Config::GameState state = gameLogic_->getGameState();
        std::string statusText;
        sf::Color statusColor = sf::Color::White;
        
        switch (state) {
            case Config::GameState::WON:
                statusText = "YOU WIN!";
                statusColor = sf::Color::Green;
                break;
            case Config::GameState::LOST:
                statusText = "GAME OVER";
                statusColor = sf::Color::Red;
                break;
            case Config::GameState::PLAYING:
            default:
                statusText = "MINESWEEPER";
                statusColor = sf::Color::Yellow;
                break;
        }
        
        // Draw status text centered in the area between the two panels
        sf::Text statusDisplay;
        statusDisplay.setFont(assetManager_->getFont());
        statusDisplay.setString(statusText);
        statusDisplay.setCharacterSize(24); // Slightly smaller to avoid overlap
        statusDisplay.setFillColor(statusColor);
        statusDisplay.setStyle(sf::Text::Bold);

        // Compute safe horizontal region between left and right panels
        float leftPanelRight = 30.0f + 140.0f; // left counter x + width
        float rightPanelLeft = static_cast<float>(Config::WINDOW_WIDTH) - 170.0f; // timer x
        float padding = 8.0f; // small padding from panels
        float leftLimit = leftPanelRight + padding;
        float rightLimit = rightPanelLeft - padding;
        float availableWidth = std::max(0.0f, rightLimit - leftLimit);

        sf::FloatRect textBounds = statusDisplay.getLocalBounds();
        float scale = 1.0f;
        if (textBounds.width > 0.0f && textBounds.width > availableWidth) {
            scale = availableWidth / textBounds.width;
        }
        statusDisplay.setScale(scale, scale);

        // Position the (possibly scaled) text centered within the safe region
        textBounds = statusDisplay.getLocalBounds(); // bounds before considering scale.left/top
        statusDisplay.setPosition(
            leftLimit + (availableWidth - textBounds.width * scale) / 2.0f - textBounds.left * scale,
            6.0f // Slight vertical offset
        );

        window.draw(statusDisplay);
        
        // Draw instructions at the bottom of UI area
        sf::Text instructions;
        instructions.setFont(assetManager_->getFont());
        
        if (state == Config::GameState::PLAYING) {
            instructions.setString("Left click: Reveal  |  Right click: Flag  |  R: Restart");
        } else {
            instructions.setString("Click smiley face or press R to restart");
        }
        
        instructions.setCharacterSize(16); // Taille augmentée
        instructions.setFillColor(sf::Color(200, 200, 200));
        
        sf::FloatRect instrBounds = instructions.getLocalBounds();
        instructions.setPosition(
            (Config::WINDOW_WIDTH - instrBounds.width) / 2 - instrBounds.left,
            Config::UI_HEIGHT - 25 // Position ajustée
        );
        
        window.draw(instructions);
        
        // Draw additional game info
        if (state == Config::GameState::PLAYING) {
            auto board = gameLogic_->getBoard();
            if (board) {
                int revealed = board->getRevealedCount();
                int totalCells = board->getWidth() * board->getHeight();
                int mines = board->getMineCount();
                
                std::string infoText = "Progress: " + std::to_string(revealed) + "/" + 
                                      std::to_string(totalCells - mines) + " safe cells";
                
                sf::Text gameInfo;
                gameInfo.setFont(assetManager_->getFont());
                gameInfo.setString(infoText);
                gameInfo.setCharacterSize(14);
                gameInfo.setFillColor(sf::Color(180, 180, 220));
                
                sf::FloatRect infoBounds = gameInfo.getLocalBounds();
                // Position the progress text below the face button to avoid overlap
                float faceTop = (Config::UI_HEIGHT - 70.0f) / 2.0f + 10.0f; // matches renderFaceButton layout
                float faceBottom = faceTop + 70.0f;
                float infoY = faceBottom + 6.0f; // small gap under the face button

                // If computed position is too low, clamp it to a reasonable area inside the UI
                if (infoY + infoBounds.height > static_cast<float>(Config::UI_HEIGHT) - 6.0f) {
                    infoY = static_cast<float>(Config::UI_HEIGHT) - infoBounds.height - 6.0f;
                }

                gameInfo.setPosition(
                    (Config::WINDOW_WIDTH - infoBounds.width) / 2.0f - infoBounds.left,
                    infoY
                );
                
                window.draw(gameInfo);
            }
        }
    }

    sf::Vector2i Renderer::screenToBoardPosition(int screenX, int screenY) const {
        int boardX = screenX / Config::TILE_SIZE;
        int boardY = (screenY - Config::UI_HEIGHT) / Config::TILE_SIZE;
        
        return sf::Vector2i(boardX, boardY);
    }

    void Renderer::drawDigit(sf::RenderWindow& window, int digit, int x, int y) {
        if (!assetManager_) return;
        
        // Since we're not using digit textures anymore, use text instead
        sf::Text digitText;
        digitText.setFont(assetManager_->getFont());
        digitText.setString(std::to_string(digit));
        digitText.setCharacterSize(36);
        digitText.setFillColor(sf::Color::Red);
        digitText.setPosition(x, y);
        
        window.draw(digitText);
    }

    void Renderer::drawNumber(sf::RenderWindow& window, int number, int x, int y, int digitCount) {
        number = std::max(0, std::min(999, number));
        
        std::string numberStr = std::to_string(number);
        while (numberStr.length() < static_cast<size_t>(digitCount)) {
            numberStr = "0" + numberStr;
        }
        
        for (size_t i = 0; i < numberStr.length(); ++i) {
            int digit = numberStr[i] - '0';
            drawDigit(window, digit, x + static_cast<int>(i) * 24, y);
        }
    }
}