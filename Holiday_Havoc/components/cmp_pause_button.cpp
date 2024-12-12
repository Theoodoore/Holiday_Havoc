#include "cmp_pause_button.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <system_resources.h>

PauseButton::PauseButton(Entity* p, const sf::Vector2f& position, std::shared_ptr<PopupComponent> popup)
    : Component(p), _position(position), _popup(popup) {
    // Set up button shape
    _button.setSize(sf::Vector2f(100.f, 50.f));  // 200x50 size
    _button.setFillColor(sf::Color::Black);       // Blue background for the button
    _button.setPosition(position);               // Set position of the button

    // Set up button text
    auto _font = Resources::get<sf::Font>("RobotoMono-Regular.ttf");
    _text.setFont(*_font);
    _text.setString("Pause");                    // The button's text
    _text.setCharacterSize(24);                  // Text size
    _text.setFillColor(sf::Color::White);        // White text
    _text.setPosition(position.x + 15.f, position.y + 10.f);  // Center the text inside the button
    
    // Add a white outline to the text
    _button.setOutlineColor(sf::Color::White);     // Set the outline color to white
    _button.setOutlineThickness(2.f);

    // Define the callback for when the button is clicked
    _onClickCallback = [popup]() {
        popup->setMode(PopupComponent::ShopSystem);
        popup->setText("Paused\n\nPress Escape to go back\nto the main menu");
        popup->moveTowerButtonsOffScreen();
        popup->show();  // Show the popup when the button is clicked
        
        std::cout << "Pause button clicked, showing popup.\n";
        };
}

void PauseButton::update(double dt) {
    // Get mouse position and check if button is clicked
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(Engine::GetWindow());
        if (_button.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
            _onClickCallback();  // Call the callback
        }
    }
}

void PauseButton::render() {
    Engine::GetWindow().draw(_button);  // Draw the button
    Engine::GetWindow().draw(_text);    // Draw the text
}
