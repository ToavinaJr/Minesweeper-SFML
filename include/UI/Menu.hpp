#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include <string>

namespace Minesweeper {
    class Menu {
    public:
        struct MenuItem {
            std::string text;
            std::function<void()> action;
            bool isSelected = false;
            bool isEnabled = true;
        };
        
        Menu(sf::RenderWindow& window);
        
        // Setup
        void setTitle(const std::string& title);
        void setPosition(float x, float y);
        void setSpacing(float spacing);
        void setFont(const sf::Font& font);
        
        // Items management
        void addItem(const std::string& text, std::function<void()> action, bool enabled = true);
        void clearItems();
        void selectItem(int index);
        int getSelectedIndex() const { return selectedIndex_; }
        
        // Interaction
        void handleEvent(const sf::Event& event);
        void update();
        void render();
        
        // Navigation
        void moveUp();
        void moveDown();
        void activateSelected();
        
    private:
        sf::RenderWindow& window_;
        sf::Font font_;
        sf::Text title_;
        std::vector<MenuItem> items_;
        
        float x_ = 0;
        float y_ = 0;
        float spacing_ = 50.0f;
        int selectedIndex_ = 0;
        
        void updateItemsDisplay();
    };
}