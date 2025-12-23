#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

namespace Minesweeper {
    class Button {
    public:
        Button();
        Button(const sf::Vector2f& position, const sf::Vector2f& size, 
               const std::string& text, const sf::Font& font);
        
        // Setup
        void setPosition(const sf::Vector2f& position);
        void setSize(const sf::Vector2f& size);
        void setText(const std::string& text);
        void setFont(const sf::Font& font);
        void setOnClick(std::function<void()> callback);
        
        // Interaction
        void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
        void update(const sf::Vector2i& mousePosition);
        
        // Rendering
        void draw(sf::RenderWindow& window) const;
        
        // State
        bool isMouseOver() const { return isMouseOver_; }
        // Additional styling/state APIs
        void setSelected(bool selected);
        void setTextSize(unsigned int size);
        void setEnabled(bool enabled);
        bool isEnabled() const { return isEnabled_; }
        // Invoke the click callback directly (used by Menu to activate programmatically)
        void invoke();
        
    private:
        sf::RectangleShape shape_;
        sf::Text text_;
        sf::Color normalColor_ = sf::Color(70, 70, 90);
        sf::Color hoverColor_ = sf::Color(90, 90, 110);
        sf::Color clickColor_ = sf::Color(110, 110, 130);
        
        std::function<void()> onClick_;
        bool isMouseOver_ = false;
        bool isPressed_ = false;
        bool isSelected_ = false;
        bool isEnabled_ = true;
        
        void updateColors();
    };
}
