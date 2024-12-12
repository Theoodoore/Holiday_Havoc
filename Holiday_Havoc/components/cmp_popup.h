// popup.h

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <ecm.h>
#include "../components/cmp_tower_button.h"
#include "../components/cmp_shop_button.h"

class PopupComponent: public Component {
    
public:
    PopupComponent() = delete;
    explicit PopupComponent(const sf::Vector2f& size, const std::string& text, unsigned int charSize);
    enum PopupMode { Start, ShopSystem, Pause };
    PopupMode _currentMode;
    void setPosition(const sf::Vector2f& pos);
    std::vector<std::shared_ptr<TowerButton>> _towerButtons;
    void addTowerButton(std::shared_ptr<TowerButton> button);
    void setText(const std::string& text);
    void show();
    void hide();
    void setMode(PopupMode mode);
    bool isVisible() const;
    void update(double dt) override;
    void moveTowerButtonsOffScreen();

    void clearTowerButtons();
    std::vector<std::shared_ptr<TowerButton>>& getTowerButtons();

    sf::Vector2f getBoxPosition() const;

    sf::FloatRect getTextBounds() const;

    void PopupComponent::changeText();


    void render() override;


protected:
    std::shared_ptr<sf::Font> _font;
    sf::RectangleShape _box;
    sf::Text _text;
    sf::RectangleShape _closeButton;
    sf::Text _closeButtonText;
    bool _visible;

    void createCloseButton();
    void renderTowerButtons();
    bool isMouseOverCloseButton(const sf::Vector2i& mousePos) const;
    bool isMouseOverButton(const sf::RectangleShape& button);

};
