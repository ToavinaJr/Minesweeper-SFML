#include "UI/Menu.hpp"
#include <iostream>

namespace Minesweeper {
    Menu::Menu(sf::RenderWindow& window) : window_(window) {
        // Default font (will be set later)
        if (!font_.loadFromFile("assets/fonts/arial.ttf")) {
            std::cerr << "Failed to load menu font" << std::endl;
        }
        
        title_.setFont(font_);
        title_.setCharacterSize(48);
        title_.setFillColor(sf::Color::Yellow);
        title_.setStyle(sf::Text::Bold);
    }
    
    void Menu::setTitle(const std::string& title) {
        title_.setString(title);
        sf::FloatRect bounds = title_.getLocalBounds();
        title_.setOrigin(bounds.width / 2, bounds.height / 2);
    }
    
    void Menu::setPosition(float x, float y) {
        x_ = x;
        y_ = y;
        updateItemsDisplay();
    }
    
    void Menu::setSpacing(float spacing) {
        spacing_ = spacing;
        updateItemsDisplay();
    }
    
    void Menu::setFont(const sf::Font& font) {
        font_ = font;
        title_.setFont(font_);
        updateItemsDisplay();
    }
    
    void Menu::addItem(const std::string& text, std::function<void()> action, bool enabled) {
        MenuItem item;
        item.text = text;
        item.action = action;
        item.isEnabled = enabled;
        item.isSelected = (items_.empty() && enabled);
        items_.push_back(item);
        updateItemsDisplay();
    }
    
    void Menu::clearItems() {
        items_.clear();
        selectedIndex_ = 0;
    }
    
    void Menu::selectItem(int index) {
        if (index >= 0 && index < static_cast<int>(items_.size()) && items_[index].isEnabled) {
            selectedIndex_ = index;
            updateItemsDisplay();
        }
    }
    
    void Menu::handleEvent(const sf::Event& event) {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Up:
                case sf::Keyboard::W:
                    moveUp();
                    break;
                    
                case sf::Keyboard::Down:
                case sf::Keyboard::S:
                    moveDown();
                    break;
                    
                case sf::Keyboard::Enter:
                case sf::Keyboard::Space:
                    activateSelected();
                    break;
                    
                default:
                    break;
            }
        }
        else if (event.type == sf::Event::MouseMoved) {
            // Mouse selection
            sf::Vector2f mousePos = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));
            
            for (size_t i = 0; i < items_.size(); ++i) {
                if (items_[i].isEnabled) {
                    // Create a temporary text to check bounds
                    sf::Text tempText;
                    tempText.setFont(font_);
                    tempText.setString(items_[i].text);
                    tempText.setCharacterSize(32);
                    tempText.setPosition(x_, y_ + 100 + i * spacing_);
                    
                    sf::FloatRect bounds = tempText.getGlobalBounds();
                    if (bounds.contains(mousePos)) {
                        selectItem(i);
                        break;
                    }
                }
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));
                
                for (size_t i = 0; i < items_.size(); ++i) {
                    if (items_[i].isEnabled) {
                        sf::Text tempText;
                        tempText.setFont(font_);
                        tempText.setString(items_[i].text);
                        tempText.setCharacterSize(32);
                        tempText.setPosition(x_, y_ + 100 + i * spacing_);
                        
                        sf::FloatRect bounds = tempText.getGlobalBounds();
                        if (bounds.contains(mousePos)) {
                            activateSelected();
                            break;
                        }
                    }
                }
            }
        }
    }
    
    void Menu::update() {
        // Animation or other updates can go here
    }
    
    void Menu::render() {
        // Draw title
        title_.setPosition(x_, y_);
        window_.draw(title_);
        
        // Draw menu items
        for (size_t i = 0; i < items_.size(); ++i) {
            sf::Text itemText;
            itemText.setFont(font_);
            itemText.setString(items_[i].text);
            itemText.setCharacterSize(32);
            itemText.setPosition(x_, y_ + 100 + i * spacing_);
            
            if (items_[i].isEnabled) {
                if (static_cast<int>(i) == selectedIndex_) {
                    itemText.setFillColor(sf::Color::Yellow);
                    itemText.setStyle(sf::Text::Bold | sf::Text::Underlined);
                } else {
                    itemText.setFillColor(sf::Color::White);
                }
            } else {
                itemText.setFillColor(sf::Color(128, 128, 128));
            }
            
            // Center text
            sf::FloatRect bounds = itemText.getLocalBounds();
            itemText.setOrigin(bounds.width / 2, bounds.height / 2);
            
            window_.draw(itemText);
        }
    }
    
    void Menu::moveUp() {
        int newIndex = selectedIndex_;
        do {
            newIndex = (newIndex - 1 + items_.size()) % items_.size();
        } while (!items_[newIndex].isEnabled && newIndex != selectedIndex_);
        
        if (items_[newIndex].isEnabled) {
            selectedIndex_ = newIndex;
            updateItemsDisplay();
        }
    }
    
    void Menu::moveDown() {
        int newIndex = selectedIndex_;
        do {
            newIndex = (newIndex + 1) % items_.size();
        } while (!items_[newIndex].isEnabled && newIndex != selectedIndex_);
        
        if (items_[newIndex].isEnabled) {
            selectedIndex_ = newIndex;
            updateItemsDisplay();
        }
    }
    
    void Menu::activateSelected() {
        if (selectedIndex_ >= 0 && selectedIndex_ < static_cast<int>(items_.size())) {
            if (items_[selectedIndex_].isEnabled && items_[selectedIndex_].action) {
                items_[selectedIndex_].action();
            }
        }
    }
    
    void Menu::updateItemsDisplay() {
        // Update text positions and properties
        title_.setPosition(x_, y_);
        
        for (size_t i = 0; i < items_.size(); ++i) {
            items_[i].isSelected = (static_cast<int>(i) == selectedIndex_);
        }
    }
}