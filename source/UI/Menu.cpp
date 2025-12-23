#include "UI/Menu.hpp"
#include "UI/Button.hpp"
#include <iostream>

namespace Minesweeper {

    Menu::Menu(sf::RenderWindow& window) : window_(window) {
        // Default font (will be set later)
        if (!font_.loadFromFile("assets/fonts/arial.ttf")) {
            std::cerr << "Failed to load menu font" << std::endl;
        }
        // default sizes
        titleSize_ = 48;
        itemSize_ = 32;

        title_.setFont(font_);
        title_.setCharacterSize(titleSize_);
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

    void Menu::setTitleSize(unsigned int size) {
        titleSize_ = size;
        title_.setCharacterSize(titleSize_);
        updateItemsDisplay();
    }

    void Menu::setItemSize(unsigned int size) {
        itemSize_ = size;
        updateItemsDisplay();
    }
    
    void Menu::addItem(const std::string& text, std::function<void()> action, bool enabled) {
        MenuItem item;
        // Create a Button for this item
        item.button = std::make_unique<Button>();
        item.button->setFont(font_);
        item.button->setText(text);
        item.button->setOnClick(action);
        item.button->setEnabled(enabled);
        item.isEnabled = enabled;
        // initial sizes/positions updated in updateItemsDisplay
        items_.push_back(std::move(item));
        // If first enabled, ensure selected index points to it
        if (items_.size() == 1 && enabled) selectedIndex_ = 0;
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
            return; // handled key event
        }

        // For mouse events, delegate to Buttons
        if (event.type == sf::Event::MouseMoved ||
            event.type == sf::Event::MouseButtonPressed ||
            event.type == sf::Event::MouseButtonReleased) {
            for (size_t i = 0; i < items_.size(); ++i) {
                if (items_[i].button) {
                    items_[i].button->handleEvent(event, window_);
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
            if (items_[i].button) {
                items_[i].button->draw(window_);
            }
        }
    }
    
    void Menu::moveUp() {
        if (items_.empty()) return;
        int newIndex = selectedIndex_;
        do {
            newIndex = (newIndex - 1 + items_.size()) % items_.size();
        } while ((items_[newIndex].button && !items_[newIndex].button->isEnabled()) && newIndex != selectedIndex_);

        if (items_[newIndex].button && items_[newIndex].button->isEnabled()) {
            selectedIndex_ = newIndex;
            updateItemsDisplay();
        }
    }
    
    void Menu::moveDown() {
        if (items_.empty()) return;
        int newIndex = selectedIndex_;
        do {
            newIndex = (newIndex + 1) % items_.size();
        } while ((items_[newIndex].button && !items_[newIndex].button->isEnabled()) && newIndex != selectedIndex_);

        if (items_[newIndex].button && items_[newIndex].button->isEnabled()) {
            selectedIndex_ = newIndex;
            updateItemsDisplay();
        }
    }
    
    void Menu::activateSelected() {
        if (selectedIndex_ >= 0 && selectedIndex_ < static_cast<int>(items_.size())) {
            if (items_[selectedIndex_].button && items_[selectedIndex_].button->isEnabled()) {
                items_[selectedIndex_].button->setSelected(true);
                items_[selectedIndex_].button->invoke();
            }
        }
    }
    
    void Menu::updateItemsDisplay() {
        // Update text positions and properties
        // Re-center title origin in case size or font changed
        sf::FloatRect tb = title_.getLocalBounds();
        title_.setOrigin(tb.left + tb.width / 2.0f, tb.top + tb.height / 2.0f);
        title_.setPosition(x_, y_);

        // Compute button sizes and positions
        float buttonWidth = 400.0f;
        float buttonHeight = static_cast<float>(itemSize_) + 16.0f; // padding

        for (size_t i = 0; i < items_.size(); ++i) {
            if (items_[i].button) {
                float bx = x_ - buttonWidth / 2.0f;
                float by = y_ + 60 + i * spacing_;
                items_[i].button->setPosition(sf::Vector2f(bx, by));
                items_[i].button->setSize(sf::Vector2f(buttonWidth, buttonHeight));
                items_[i].button->setFont(font_);
                items_[i].button->setTextSize(itemSize_);
                items_[i].button->setSelected(static_cast<int>(i) == selectedIndex_);
            }
        }
    }

    float Menu::getBottom() const {
        if (items_.empty()) {
            return y_ + 60.0f; // start area if no items
        }

        float buttonHeight = static_cast<float>(itemSize_) + 16.0f;
        size_t lastIndex = items_.size() - 1;
        float lastY = y_ + 60.0f + static_cast<float>(lastIndex) * spacing_;
        return lastY + buttonHeight; // bottom of last button
    }

    float Menu::getLastButtonTop() const {
        if (items_.empty()) {
            return y_ + 60.0f;
        }
        size_t lastIndex = items_.size() - 1;
        float lastY = y_ + 60.0f + static_cast<float>(lastIndex) * spacing_;
        return lastY;
    }
}