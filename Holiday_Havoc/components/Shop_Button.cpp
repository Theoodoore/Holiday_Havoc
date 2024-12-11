#include "Shop_Button.h"
#include "engine.h"
#include <iostream> // For debug output

ShopButton::ShopButton(Entity* p, sf::Texture* spriteSheet, const sf::Vector2f& position,
    const sf::IntRect& staticRect, const sf::IntRect& hoverRect,
    const sf::IntRect& clickRect, const std::function<void()>& onClick)
    : Component(p), _spriteSheet(spriteSheet), _staticRect(staticRect), _hoverRect(hoverRect),
    _clickRect(clickRect), _onClick(onClick), _isHovered(false), _isClicked(false) {
    if (!_spriteSheet) {
        throw std::runtime_error("ShopButton: spriteSheet is null!");
    }

    // Set up the sprite
    _buttonSprite.setTexture(*_spriteSheet);
    _buttonSprite.setTextureRect(_staticRect); // Default to static state
    _buttonSprite.setPosition(position);

    _buttonSprite.setScale(1.f, 1.f);

    // Calculate scaling to ensure the button appears at the correct size
    const float desiredWidth = 160.0f; // Example: Desired display width
    const float desiredHeight = 80.0f; // Example: Desired display height
    float scaleX = desiredWidth / _staticRect.width;
    float scaleY = desiredHeight / _staticRect.height;
    _buttonSprite.setScale(scaleX, scaleY);

    // Debug logging
    std::cout << "ShopButton created at position (" << position.x << ", " << position.y << ") with scale ("
        << scaleX << ", " << scaleY << ")" << std::endl;
}

void ShopButton::update(double dt) {
    // Get the mouse position in the game window
    sf::Vector2f mousePos = Engine::GetWindow().mapPixelToCoords(sf::Mouse::getPosition(Engine::GetWindow()));
    _isHovered = _buttonSprite.getGlobalBounds().contains(mousePos);

    if (_isHovered) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (!_isClicked) {
                _isClicked = true;
                _buttonSprite.setTextureRect(_clickRect); // Click state
                _onClick(); // Perform the button's action
                std::cout << "ShopButton clicked!" << std::endl; // Debug
            }
        }
        else {
            _isClicked = false;
            _buttonSprite.setTextureRect(_hoverRect); // Hover state
        }
    }
    else {
        _isClicked = false;
        _buttonSprite.setTextureRect(_staticRect); // Static state
    }
}

void ShopButton::render() {
    Engine::GetWindow().draw(_buttonSprite); // Draw the button
}
