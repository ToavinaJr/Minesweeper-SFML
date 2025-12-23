#include "../../include/Logic/Board.hpp"
#include <random>
#include <queue>
#include <utility>
#include <iostream>

namespace Minesweeper {
    Board::Board(int width, int height, int mineCount) 
        : width_(width), height_(height), mineCount_(mineCount) {
        cells_.resize(height_, std::vector<Cell>(width_));
        reset();
    }

    void Board::reset() {
        for (auto& row : cells_) {
            for (auto& cell : row) {
                cell.reset();
            }
        }
        isInitialized_ = false;
    }

    void Board::initialize(int firstClickX, int firstClickY) {
        if (!isInitialized_) {
            placeMines(firstClickX, firstClickY);
            calculateAdjacentMines();
            isInitialized_ = true;
        }
    }

    Cell& Board::getCell(int x, int y) {
        return cells_[y][x];
    }

    const Cell& Board::getCell(int x, int y) const {
        return cells_[y][x];
    }

    void Board::placeMines(int safeX, int safeY) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distWidth(0, width_ - 1);
        std::uniform_int_distribution<> distHeight(0, height_ - 1);
        
        int minesPlaced = 0;
        
        // Ensure first click position is safe
        std::vector<std::pair<int, int>> safeCells;
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                int nx = safeX + dx;
                int ny = safeY + dy;
                if (isCellValid(nx, ny)) {
                    safeCells.emplace_back(nx, ny);
                }
            }
        }
        
        while (minesPlaced < mineCount_) {
            int x = distWidth(gen);
            int y = distHeight(gen);
            
            // Check if this is a safe cell (around first click)
            bool isSafeCell = false;
            for (const auto& safe : safeCells) {
                if (x == safe.first && y == safe.second) {
                    isSafeCell = true;
                    break;
                }
            }
            
            if (!isSafeCell && !cells_[y][x].hasMine()) {
                cells_[y][x].setMine(true);
                minesPlaced++;
            }
        }
    }

    void Board::calculateAdjacentMines() {
        static const int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        static const int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        
        for (int y = 0; y < height_; ++y) {
            for (int x = 0; x < width_; ++x) {
                if (cells_[y][x].hasMine()) {
                    continue;
                }
                
                int mineCount = 0;
                for (int i = 0; i < 8; ++i) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    
                    if (isCellValid(nx, ny) && cells_[ny][nx].hasMine()) {
                        mineCount++;
                    }
                }
                
                cells_[y][x].setAdjacentMines(mineCount);
            }
        }
    }

    bool Board::revealCell(int x, int y) {
        if (!isCellValid(x, y) || !isInitialized_) {
            return false;
        }
        
        Cell& cell = cells_[y][x];
        
        if (cell.isRevealed() || cell.isFlagged()) {
            return false;
        }
        
        cell.reveal();
        
        if (cell.hasMine()) {
            return true; // Game over
        }
        
        if (cell.getAdjacentMines() == 0) {
            revealEmptyCells(x, y);
        }
        
        return false;
    }

    void Board::revealEmptyCells(int x, int y) {
        std::queue<std::pair<int, int>> cellsToCheck;
        cellsToCheck.emplace(x, y);
        
        static const int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        static const int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        
        while (!cellsToCheck.empty()) {
            auto [currentX, currentY] = cellsToCheck.front();
            cellsToCheck.pop();
            
            for (int i = 0; i < 8; ++i) {
                int nx = currentX + dx[i];
                int ny = currentY + dy[i];
                
                if (isCellValid(nx, ny)) {
                    Cell& neighbor = cells_[ny][nx];
                    
                    if (!neighbor.isRevealed() && !neighbor.isFlagged() && !neighbor.hasMine()) {
                        neighbor.reveal();
                        
                        if (neighbor.getAdjacentMines() == 0) {
                            cellsToCheck.emplace(nx, ny);
                        }
                    }
                }
            }
        }
    }

    void Board::toggleFlag(int x, int y) {
        if (isCellValid(x, y)) {
            cells_[y][x].toggleFlag();
        }
    }

    bool Board::checkWin() const {
        for (const auto& row : cells_) {
            for (const auto& cell : row) {
                if (!cell.hasMine() && !cell.isRevealed()) {
                    return false;
                }
                if (cell.hasMine() && !cell.isFlagged()) {
                    return false;
                }
            }
        }
        return true;
    }

    bool Board::isCellValid(int x, int y) const {
        return x >= 0 && x < width_ && y >= 0 && y < height_;
    }

    int Board::getFlagCount() const {
        int count = 0;
        for (const auto& row : cells_) {
            for (const auto& cell : row) {
                if (cell.isFlagged()) {
                    count++;
                }
            }
        }
        return count;
    }

    int Board::getRevealedCount() const {
        int count = 0;
        for (const auto& row : cells_) {
            for (const auto& cell : row) {
                if (cell.isRevealed()) {
                    count++;
                }
            }
        }
        return count;
    }
}
