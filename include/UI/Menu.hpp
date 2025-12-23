#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <functional>
#include <string>
#include "UI/Button.hpp"

namespace Minesweeper {
    class Menu {
    public:
        struct MenuItem {
            std::unique_ptr<Button> button;
            bool isSelected = false;
            bool isEnabled = true;
        };
        
        Menu(sf::RenderWindow& window);
        
        // Setup
        void setTitle(const std::string& title);
        void setPosition(float x, float y);
        void setSpacing(float spacing);
        void setFont(const sf::Font& font);
        // Text sizing
        void setTitleSize(unsigned int size);
        void setItemSize(unsigned int size);
        
        // Items management
        void addItem(const std::string& text, std::function<void()> action, bool enabled = true);
        void clearItems();
        void selectItem(int index);
        int getSelectedIndex() const { return selectedIndex_; }
        
        // Interaction
        void handleEvent(const sf::Event& event);
        void update();
        void render();

        // Utility
        // Return the y-coordinate (in window space) of the bottom of the menu items area
        float getBottom() const;
        // Return the y-coordinate of the top of the last menu button (useful for placing items above it)
        float getLastButtonTop() const;
        
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
        unsigned int titleSize_ = 48;
        unsigned int itemSize_ = 32;
        
        void updateItemsDisplay();
    };
}