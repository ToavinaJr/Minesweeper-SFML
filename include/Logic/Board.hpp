#pragma once
#include <vector>
#include <memory>
#include "Cell.hpp"
#include "../Game/Config.hpp"

namespace Minesweeper {
    class Board {
    public:
        Board(int width = Config::BOARD_WIDTH, 
              int height = Config::BOARD_HEIGHT, 
              int mineCount = Config::MINES_COUNT);
        
        // Initialization
        void initialize(int firstClickX, int firstClickY);
        void reset();
        
        // Cell access
        Cell& getCell(int x, int y);
        const Cell& getCell(int x, int y) const;
        
        // Game actions
        bool revealCell(int x, int y);
        void toggleFlag(int x, int y);
        
        // Game state checks
        bool checkWin() const;
        bool isCellValid(int x, int y) const;
        
        // Getters
        int getWidth() const { return width_; }
        int getHeight() const { return height_; }
        int getMineCount() const { return mineCount_; }
        int getFlagCount() const;
        int getRevealedCount() const;
        
    private:
        void placeMines(int safeX, int safeY);
        void calculateAdjacentMines();
        void revealEmptyCells(int x, int y);
        
        int width_;
        int height_;
        int mineCount_;
        std::vector<std::vector<Cell>> cells_;
        bool isInitialized_ = false;
    };
}
