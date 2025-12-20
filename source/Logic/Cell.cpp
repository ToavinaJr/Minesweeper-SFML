#include "../../include/Logic/Cell.hpp"

namespace Minesweeper {
    Cell::Cell() {
        reset();
    }

    void Cell::toggleFlag() {
        if (!isRevealed_) {
            isFlagged_ = !isFlagged_;
        }
    }

    void Cell::reveal() {
        if (!isFlagged_) {
            isRevealed_ = true;
        }
    }

    void Cell::reset() {
        hasMine_ = false;
        isRevealed_ = false;
        isFlagged_ = false;
        adjacentMines_ = 0;
    }
}
