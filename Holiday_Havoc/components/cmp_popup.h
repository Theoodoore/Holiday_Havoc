#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <ecm.h>

class PopupComponent: public Component {
    
public:
    PopupComponent() = delete;
    explicit PopupComponent(Entity* p, const sf::Vector2f& size, const std::string& text, unsigned int charSize);
    void setPosition(const sf::Vector2f& pos);
    void setText(const std::string& text);
    void show();
    void hide();
    bool isVisible() const;
    void update(double dt) override;

    void render() override;

    ~PopupComponent() override = default;

protected:
    std::shared_ptr<sf::Font> _font;
    sf::RectangleShape _box;
    sf::Text _text;
    sf::RectangleShape _closeButton;
    sf::Text _closeButtonText;
    bool _visible;

    void createCloseButton();
    bool isMouseOverCloseButton(const sf::Vector2i& mousePos) const;

};
