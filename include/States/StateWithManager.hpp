#pragma once
#include "GameState.hpp"
#include "StateManager.hpp"

namespace Minesweeper {
    class StateWithManager : public GameState {
    protected:
        sf::RenderWindow& window_;
        StateManager& stateManager_;
        
        ~StateWithManager() = default;
        StateWithManager(sf::RenderWindow& window, StateManager& stateManager)
            : window_(window), stateManager_(stateManager) {}
    };

}