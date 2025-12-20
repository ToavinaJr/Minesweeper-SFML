#pragma once
#include <memory>
#include "Board.hpp"
#include "../Game/Config.hpp"

namespace Minesweeper {
    class GameLogic {
    public:
        GameLogic();
        
        // Game control
        void startNewGame();
        void handleLeftClick(int x, int y);
        void handleRightClick(int x, int y);
        
        // State checks
        bool isGameOver() const;
        bool isGameWon() const;
        Config::GameState getGameState() const { return gameState_; }
        
        // Getters
        std::shared_ptr<Board> getBoard() const { return board_; }
        int getGameTime() const { return gameTime_; }
        
        // Update
        void update(float deltaTime);
        
    private:
        std::shared_ptr<Board> board_;
        Config::GameState gameState_ = Config::GameState::PLAYING;
        float elapsedTime_ = 0.0f;
        int gameTime_ = 0;
        bool firstClick_ = true;
        
        void checkGameState();
    };
}
