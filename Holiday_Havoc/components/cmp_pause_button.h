#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>  // For std::shared_ptr
#include "cmp_popup.h"  // Assuming you have this header for PopupComponent
#include "ecm.h"  // Assuming you are using an entity-component system

class PauseButton : public Component {
private:
    sf::RectangleShape _button;  // The button's visual representation
    sf::Text _text;              // The text that says "Pause"
    std::function<void()> _onClickCallback;  // The callback when clicked
    std::shared_ptr<PopupComponent> _popup;  // Pointer to the PopupComponent
  //  sf::Font _font;             // Font for the text
    sf::Vector2f _position;     // Position of the button

public:
    // Constructor that creates a "Pause" button at a given position
    PauseButton(Entity* p, const sf::Vector2f& position, std::shared_ptr<PopupComponent> popup);


    void update(double dt) override;
    void render() override;

};
