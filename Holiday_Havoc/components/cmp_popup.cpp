#include "cmp_popup.h"
#include <system_renderer.h>
#include <system_resources.h>
#include "engine.h"
#include <iostream>

PopupComponent::PopupComponent(Entity* const p, const sf::Vector2f& size, const std::string& text, unsigned int charSize)
    : Component(nullptr), _visible(false) {

    // Load font for the popup
    _font = Resources::get<sf::Font>("RobotoMono-Regular.ttf");
    // Initialize the rectangle box
    _box.setSize(size);
    _box.setFillColor(sf::Color(0, 0, 0, 200)); // Semi-transparent black
    _box.setOutlineColor(sf::Color::White);
    _box.setOutlineThickness(2.f);

    // Initialize the text
    _text.setFont(*_font);
    _text.setString(text);
    _text.setCharacterSize(charSize);
    _text.setFillColor(sf::Color::White);

    createCloseButton();
}

void PopupComponent::update(double dt) {

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))  
        {

            sf::Vector2i mousePos = sf::Mouse::getPosition(Engine::GetWindow());
            if (isMouseOverCloseButton(mousePos)) {
                hide();
            }
        }

}


bool PopupComponent::isMouseOverCloseButton(const sf::Vector2i& mousePos) const {
    return _closeButton.getGlobalBounds().contains(sf::Vector2f(mousePos)); // Check if mouse position is within the button's bounds
}

void PopupComponent::setPosition(const sf::Vector2f& pos) {
    _box.setPosition(pos);
    _text.setPosition(pos.x + 20.f, pos.y + 20.f); // Add padding for the text
    _closeButton.setPosition(pos.x + _box.getSize().x - _closeButton.getSize().x - 10.f, pos.y + _box.getSize().y - _closeButton.getSize().y - 10.f);
    // Ensure button position is set first before positioning text
    _closeButtonText.setPosition(_closeButton.getPosition().x + 5.f,
        _closeButton.getPosition().y + 5.f);
}

void PopupComponent::setText(const std::string& text) {
    _text.setString(text);
}

void PopupComponent::show() {
    _visible = true;
}

void PopupComponent::hide() {
    _visible = false;
}

bool PopupComponent::isVisible() const {
    return _visible;
}

void PopupComponent::render() {
    if (_visible) {
        Renderer::queue(&_box);  // Render the box
        Renderer::queue(&_text); // Render the text
        Renderer::queue(&_closeButton); // Render the close button (X)
        Renderer::queue(&_closeButtonText);
    }
}

void PopupComponent::createCloseButton() {
    _closeButton.setSize(sf::Vector2f(80.f, 40.f)); // Size of the button
    _closeButton.setFillColor(sf::Color(0, 0, 0, 180)); // Semi-transparent black background for the button
    _closeButton.setOutlineThickness(2.f);
    _closeButton.setOutlineColor(sf::Color::White);

    // Set up the text inside the button
    _closeButtonText.setFont(*_font);
    _closeButtonText.setString("Start");
    _closeButtonText.setCharacterSize(24);
    _closeButtonText.setFillColor(sf::Color::White);



}
