#include "../../include/UI/UIManager.hpp"

namespace Minesweeper {
    UIManager::UIManager(std::shared_ptr<GameLogic> gameLogic,
                        std::shared_ptr<AssetManager> assetManager)
        : gameLogic_(gameLogic), assetManager_(assetManager) {
        setupUI();
    }

    void UIManager::setupUI() {
        // Setup UI panel
        uiPanel_.setSize(sf::Vector2f(Config::WINDOW_WIDTH, Config::UI_HEIGHT));
        uiPanel_.setFillColor(sf::Color(Config::UI_BACKGROUND_COLOR));
        
        // Setup new game button (face button is rendered separately)
    }

    void UIManager::update(float deltaTime) {
        // Update any UI animations or states
    }

    void UIManager::render(sf::RenderWindow& window) {
        window.draw(uiPanel_);
        renderGameInfo(window);
        renderFaceButton(window);
    }

    void UIManager::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
        newGameButton_.handleEvent(event, window);
    }

    void UIManager::renderGameInfo(sf::RenderWindow& window) {
        if (!gameLogic_ || !assetManager_) return;
        
        auto board = gameLogic_->getBoard();
        if (!board) return;
        
        // Render mine counter
        int minesLeft = board->getMineCount() - board->getFlagCount();
        std::string mineText = std::to_string(minesLeft);
        
        // Render timer
        int gameTime = gameLogic_->getGameTime();
        std::string timeText = std::to_string(gameTime);
        
        // You would typically use the Renderer class for this,
        // but for simplicity we're doing basic text rendering here
        sf::Text mineCounter;
        mineCounter.setFont(assetManager_->getFont());
        mineCounter.setString("Mines: " + mineText);
        mineCounter.setCharacterSize(24);
        mineCounter.setFillColor(sf::Color::White);
        mineCounter.setPosition(20, 20);
        window.draw(mineCounter);
        
        sf::Text timer;
        timer.setFont(assetManager_->getFont());
        timer.setString("Time: " + timeText);
        timer.setCharacterSize(24);
        timer.setFillColor(sf::Color::White);
        timer.setPosition(Config::WINDOW_WIDTH - 150, 20);
        window.draw(timer);
    }

    void UIManager::renderFaceButton(sf::RenderWindow& window) {
        if (!gameLogic_ || !assetManager_) return;
        
        Config::GameState state = gameLogic_->getGameState();
        const sf::Texture& faceTexture = assetManager_->getFaceTexture(state);
        
        sf::Sprite faceSprite(faceTexture);
        
        // Center the face button
        float x = (Config::WINDOW_WIDTH - 50) / 2.0f;
        float y = (Config::UI_HEIGHT - 50) / 2.0f;
        
        faceSprite.setPosition(x, y);
        
        // Scale to 50x50
        sf::Vector2u texSize = faceTexture.getSize();
        if (texSize.x != 50 || texSize.y != 50) {
            faceSprite.setScale(50.0f / texSize.x, 50.0f / texSize.y);
        }
        
        window.draw(faceSprite);
    }

    bool UIManager::isFaceButtonClicked(const sf::Vector2i& mousePos) const {
        float faceX = (Config::WINDOW_WIDTH - 50) / 2.0f;
        float faceY = (Config::UI_HEIGHT - 50) / 2.0f;
        
        return mousePos.x >= faceX && mousePos.x <= faceX + 50 &&
               mousePos.y >= faceY && mousePos.y <= faceY + 50;
    }
}
