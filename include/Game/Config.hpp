#pragma once

namespace Minesweeper {
    struct Config {
        // Board configuration
        static constexpr int BOARD_WIDTH = 16;
        static constexpr int BOARD_HEIGHT = 16;
        static constexpr int MINES_COUNT = 40;
        
        // Tile configuration
        static constexpr int TILE_SIZE = 32;
        static constexpr int UI_HEIGHT = 164;
        
        // Window configuration
        static constexpr int WINDOW_WIDTH = BOARD_WIDTH * TILE_SIZE;
        static constexpr int WINDOW_HEIGHT = BOARD_HEIGHT * TILE_SIZE + UI_HEIGHT;
        
        // Colors
        static constexpr unsigned int BACKGROUND_COLOR = 0x1E1E2EFF;
        static constexpr unsigned int UI_BACKGROUND_COLOR = 0x181825FF;
        
        // Game states
        enum class GameState {
            PLAYING,
            WON,
            LOST
        };
    };
}
