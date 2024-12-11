// Shop_Button.h

#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "ecm.h"

class ShopButton : public Component {
private:
    sf::Texture* _spriteSheet;
    sf::Sprite _buttonSprite;
    sf::IntRect _staticRect;
    sf::IntRect _hoverRect;
    sf::IntRect _clickRect;
    std::function<void()> _onClick;

    bool _isHovered;
    bool _isClicked;

public:
    ShopButton(Entity* p, sf::Texture* spriteSheet, const sf::Vector2f& position,
        const sf::IntRect& staticRect, const sf::IntRect& hoverRect,
        const sf::IntRect& clickRect, const std::function<void()>& onClick);

    void update(double dt) override;
    void render() override;
};
