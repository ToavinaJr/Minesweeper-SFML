#pragma once

namespace Minesweeper {
    class Cell {
    public:
        Cell();
        
        // Getters
        bool hasMine() const { return hasMine_; }
        bool isRevealed() const { return isRevealed_; }
        bool isFlagged() const { return isFlagged_; }
        int getAdjacentMines() const { return adjacentMines_; }
        
        // Setters
        void setMine(bool hasMine) { hasMine_ = hasMine; }
        void setRevealed(bool revealed) { isRevealed_ = revealed; }
        void setFlagged(bool flagged) { isFlagged_ = flagged; }
        void setAdjacentMines(int count) { adjacentMines_ = count; }
        
        // Actions
        void toggleFlag();
        void reveal();
        void reset();
        
    private:
        bool hasMine_ = false;
        bool isRevealed_ = false;
        bool isFlagged_ = false;
        int adjacentMines_ = 0;
    };
}
