#include "../include/Game/Game.hpp"
#include <iostream>

int main() {
    try {
        Minesweeper::Game game;
        game.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
