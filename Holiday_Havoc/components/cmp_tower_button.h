#ifndef TOWERBUTTON_H
#define TOWERBUTTON_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "tower.h"  // Assuming you have a Tower class

class TowerButton {
public:
    // Constructor to initialize the button with a tower, price, and position
    TowerButton(std::shared_ptr<Tower> tower, int price, const sf::Vector2f& position);

    void TowerButton::setPosition(const sf::Vector2f& position);

    // Render the button to the screen
    void render(sf::RenderWindow& window);

    // Check if the mouse is over the button
    bool isMouseOver(const sf::Vector2i& mousePos) const;

    // Accessor for the tower
    std::shared_ptr<Tower> getTower() const;

    // Get the price of the tower
    int getPrice() const;

    sf::Vector2f getSize() const;

private:
    sf::RectangleShape _button;  // Visual representation of the button
    sf::Text _buttonText;       // Text to display on the button
    std::shared_ptr<Tower> _tower;  // Associated tower for this button
    int _price;  // Price of the tower

};

#endif // TOWERBUTTON_H
