#include "../../include/Logic/GameLogic.hpp"
#include <iostream>

namespace Minesweeper {
    GameLogic::GameLogic() {
        board_ = std::make_shared<Board>();
    }

    void GameLogic::startNewGame() {
        board_->reset();
        gameState_ = Config::GameState::PLAYING;
        elapsedTime_ = 0.0f;
        gameTime_ = 0;
        firstClick_ = true;
    }

    void GameLogic::handleLeftClick(int x, int y) {
        if (gameState_ != Config::GameState::PLAYING || !board_->isCellValid(x, y)) {
            return;
        }
        
        if (firstClick_) {
            board_->initialize(x, y);
            firstClick_ = false;
        }
        
        Cell& cell = board_->getCell(x, y);
        
        if (!cell.isFlagged()) {
            bool hitMine = board_->revealCell(x, y);
            
            if (hitMine) {
                gameState_ = Config::GameState::LOST;
            } else if (board_->checkWin()) {
                gameState_ = Config::GameState::WON;
            }
        }
    }

    void GameLogic::handleRightClick(int x, int y) {
        if (gameState_ != Config::GameState::PLAYING || !board_->isCellValid(x, y)) {
            return;
        }
        
        Cell& cell = board_->getCell(x, y);
        
        if (!cell.isRevealed()) {
            board_->toggleFlag(x, y);
            
            // Check win condition after flagging
            if (board_->checkWin()) {
                gameState_ = Config::GameState::WON;
            }
        }
    }

    bool GameLogic::isGameOver() const {
        return gameState_ == Config::GameState::LOST;
    }

    bool GameLogic::isGameWon() const {
        return gameState_ == Config::GameState::WON;
    }

    void GameLogic::update(float deltaTime) {
        if (gameState_ == Config::GameState::PLAYING && !firstClick_) {
            elapsedTime_ += deltaTime;
            if (elapsedTime_ >= 1.0f) {
                gameTime_++;
                elapsedTime_ -= 1.0f;
            }
        }
    }
}
