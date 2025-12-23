#pragma once

namespace Minesweeper {
    struct Config {
        // Difficultés prédéfinies
        enum class Difficulty {
            BEGINNER,
            INTERMEDIATE,
            EXPERT,
            CUSTOM
        };
        
        struct DifficultySettings {
            int width;
            int height;
            int mines;
            int timeLimit; // 0 = pas de limite de temps
        };
        
        // Board configuration par défaut
        static constexpr int BOARD_WIDTH = 16;
        static constexpr int BOARD_HEIGHT = 16;
        static constexpr int MINES_COUNT = 40;
        static constexpr int TIME_LIMIT = 0; // 0 = pas de limite
        
        // Tile configuration
        static constexpr int TILE_SIZE = 32;
        static constexpr int UI_HEIGHT = 180;
        
        // Window configuration
        static constexpr int WINDOW_WIDTH = BOARD_WIDTH * TILE_SIZE;
        static constexpr int WINDOW_HEIGHT = BOARD_HEIGHT * TILE_SIZE + UI_HEIGHT;
        
        // Colors
        static constexpr unsigned int BACKGROUND_COLOR = 0x1E1E2EFF;
        static constexpr unsigned int UI_BACKGROUND_COLOR = 0x181825FF;
        static constexpr unsigned int MENU_BACKGROUND_COLOR = 0x2D2D44FF;
        
        // Game states
        enum class GameState {
            PLAYING,
            WON,
            LOST,
            PAUSED
        };
        
        // Récupérer les paramètres d'une difficulté
        static DifficultySettings getDifficultySettings(Difficulty diff) {
            switch (diff) {
                case Difficulty::BEGINNER:
                    return {9, 9, 10, 180}; // 3 minutes
                case Difficulty::INTERMEDIATE:
                    return {16, 16, 40, 300}; // 5 minutes
                case Difficulty::EXPERT:
                    return {30, 16, 99, 420}; // 7 minutes
                case Difficulty::CUSTOM:
                default:
                    return {BOARD_WIDTH, BOARD_HEIGHT, MINES_COUNT, TIME_LIMIT};
            }
        }
        
        // Nom de la difficulté
        static const char* getDifficultyName(Difficulty diff) {
            switch (diff) {
                case Difficulty::BEGINNER: return "Débutant";
                case Difficulty::INTERMEDIATE: return "Intermédiaire";
                case Difficulty::EXPERT: return "Expert";
                case Difficulty::CUSTOM: return "Personnalisé";
                default: return "Inconnu";
            }
        }
    };
}