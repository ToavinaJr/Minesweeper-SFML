#include "../../include/UI/Button.hpp"
#include <iostream>

namespace Minesweeper {
    Button::Button() {
        shape_.setFillColor(normalColor_);
    }

    Button::Button(const sf::Vector2f& position, const sf::Vector2f& size,
                   const std::string& text, const sf::Font& font)
        : shape_(size) {
        shape_.setPosition(position);
        shape_.setFillColor(normalColor_);
        
        text_.setFont(font);
        text_.setString(text);
        text_.setCharacterSize(20);
        text_.setFillColor(sf::Color::White);
        
        // Center text
        sf::FloatRect textBounds = text_.getLocalBounds();
        text_.setOrigin(textBounds.left + textBounds.width / 2.0f,
                       textBounds.top + textBounds.height / 2.0f);
        text_.setPosition(position.x + size.x / 2.0f,
                         position.y + size.y / 2.0f);
    }

    void Button::setPosition(const sf::Vector2f& position) {
        shape_.setPosition(position);
        
        // Update text position
        sf::FloatRect textBounds = text_.getLocalBounds();
        sf::Vector2f size = shape_.getSize();
        text_.setPosition(position.x + size.x / 2.0f,
                         position.y + size.y / 2.0f);
    }

    void Button::setSize(const sf::Vector2f& size) {
        shape_.setSize(size);
        
        // Update text position
        sf::Vector2f position = shape_.getPosition();
        text_.setPosition(position.x + size.x / 2.0f,
                         position.y + size.y / 2.0f);
    }

    void Button::setText(const std::string& text) {
        text_.setString(text);
        
        // Re-center text
        sf::FloatRect textBounds = text_.getLocalBounds();
        text_.setOrigin(textBounds.left + textBounds.width / 2.0f,
                       textBounds.top + textBounds.height / 2.0f);
        
        sf::Vector2f position = shape_.getPosition();
        sf::Vector2f size = shape_.getSize();
        text_.setPosition(position.x + size.x / 2.0f,
                         position.y + size.y / 2.0f);
    }

    void Button::setFont(const sf::Font& font) {
        text_.setFont(font);
    }

    void Button::setOnClick(std::function<void()> callback) {
        onClick_ = callback;
    }

    void Button::setSelected(bool selected) {
        isSelected_ = selected;
        updateColors();
    }

    void Button::setTextSize(unsigned int size) {
        text_.setCharacterSize(size);
        // Re-center text
        sf::FloatRect textBounds = text_.getLocalBounds();
        text_.setOrigin(textBounds.left + textBounds.width / 2.0f,
                       textBounds.top + textBounds.height / 2.0f);
        sf::Vector2f position = shape_.getPosition();
        sf::Vector2f sizeRect = shape_.getSize();
        text_.setPosition(position.x + sizeRect.x / 2.0f,
                         position.y + sizeRect.y / 2.0f);
    }

    void Button::setEnabled(bool enabled) {
        isEnabled_ = enabled;
        updateColors();
    }

    void Button::invoke() {
        if (onClick_ && isEnabled_) {
            onClick_();
        }
    }

    void Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
        if (event.type == sf::Event::MouseMoved) {
            update(sf::Mouse::getPosition(window));
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left && isMouseOver_) {
                isPressed_ = true;
                updateColors();
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left && isMouseOver_ && isPressed_) {
                if (onClick_) {
                    onClick_();
                }
                isPressed_ = false;
                updateColors();
            }
        }
    }

    void Button::update(const sf::Vector2i& mousePosition) {
        sf::Vector2f pos = shape_.getPosition();
        sf::Vector2f size = shape_.getSize();
        
        isMouseOver_ = mousePosition.x >= pos.x &&
                      mousePosition.x <= pos.x + size.x &&
                      mousePosition.y >= pos.y &&
                      mousePosition.y <= pos.y + size.y;
        
        updateColors();
    }

    void Button::draw(sf::RenderWindow& window) const {
        window.draw(shape_);
        window.draw(text_);
    }

    void Button::updateColors() {
        if (!isEnabled_) {
            shape_.setFillColor(sf::Color(60, 60, 70));
            text_.setFillColor(sf::Color(160, 160, 160));
            return;
        }

        if (isPressed_) {
            shape_.setFillColor(clickColor_);
        }
        else if (isSelected_) {
            shape_.setFillColor(hoverColor_);
            text_.setFillColor(sf::Color::Yellow);
        }
        else if (isMouseOver_) {
            shape_.setFillColor(hoverColor_);
            text_.setFillColor(sf::Color::White);
        }
        else {
            shape_.setFillColor(normalColor_);
            text_.setFillColor(sf::Color::White);
        }
    }
}
