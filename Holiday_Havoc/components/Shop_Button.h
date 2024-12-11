#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "ecm.h"

class ShopButton : public Component {
private:
    sf::Texture* _spriteSheet;        // Reference to the sprite sheet
    sf::Sprite _buttonSprite;         // The button sprite
    sf::IntRect _staticRect;          // Rectangle for static state
    sf::IntRect _hoverRect;           // Rectangle for hover state
    sf::IntRect _clickRect;           // Rectangle for click state
    std::function<void()> _onClick;   // Action to perform on click

    bool _isHovered;                  // Is the mouse hovering over the button
    bool _isClicked;                  // Is the button being clicked

public:
    ShopButton(Entity* p, sf::Texture* spriteSheet, const sf::Vector2f& position,
        const sf::IntRect& staticRect, const sf::IntRect& hoverRect,
        const sf::IntRect& clickRect, const std::function<void()>& onClick);

    void update(double dt) override;
    void render() override;
};
