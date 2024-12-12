// cmp_tower_button.cpp
#include "cmp_tower_button.h"
#include <system_resources.h>
#include <SFML/Graphics.hpp>
#include <system_renderer.h>

TowerButton::TowerButton(std::shared_ptr<Tower> tower, int price, const sf::Vector2f& position)
    : _tower(tower), _price(price) {


}

void TowerButton::setOnClickCallback(std::function<void()> callback) {
        _onClickCallback = callback;
}

void TowerButton::onClick() {
 
        if (_onClickCallback) {
            _onClickCallback(); // Trigger the callback when clicked
        }
}


bool TowerButton::isPressed() {
    // Check if the mouse press is within the bounds of the button
        // Get the current mouse position in world coordinates
   
    sf::Vector2i mousePos = sf::Mouse::getPosition(Engine::GetWindow());
    sf::Vector2f worldPos = Engine::GetWindow().mapPixelToCoords(mousePos);

    // Check if the left mouse button is pressed and the mouse is over the button
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _button.getGlobalBounds().contains(worldPos)) {
        return true;; // Trigger the onClick callback
    }

}



void TowerButton::render(sf::RenderWindow& window) {
    Renderer::queue(&_button);
    Renderer::queue(&_buttonText);
}

bool TowerButton::isMouseOver(const sf::Vector2i& mousePos) const {
    return _button.getGlobalBounds().contains(sf::Vector2f(mousePos));  // Check if the mouse is within the button bounds
}

std::shared_ptr<Tower> TowerButton::getTower() const {
    return _tower;  // Return the tower associated with this button
}

int TowerButton::getPrice() const {
    return _price;  // Return the price of the tower
}


void TowerButton::setPosition(const sf::Vector2f& position) {
    // Set the button's size and position
    _button.setSize(sf::Vector2f(75.f, 25.f));  // Example size for the button
    _button.setPosition(position); // Position of the button
    _button.setFillColor(sf::Color::Black);  // Black fill color
    _button.setOutlineThickness(2.f);  // White border thickness
    _button.setOutlineColor(sf::Color::White);

    // Load font and set text properties
    auto font = Resources::get<sf::Font>("RobotoMono-Regular.ttf");
    _buttonText.setFont(*font);
    _buttonText.setString("Buy");
    _buttonText.setCharacterSize(18);
    _buttonText.setFillColor(sf::Color::White);

    // Center the text within the button
    sf::FloatRect textBounds = _buttonText.getLocalBounds();
    _buttonText.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    _buttonText.setPosition(
        _button.getPosition().x + _button.getSize().x / 2.f,
        _button.getPosition().y + _button.getSize().y / 2.f
    );
}

sf::Vector2f TowerButton::getSize() const {
    return _button.getSize();  // Return the size of the button for positioning
}
