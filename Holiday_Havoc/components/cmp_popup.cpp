#include "cmp_popup.h"
#include "engine.h"
#include <system_renderer.h>
#include <system_resources.h>
#include "../scenes/scene_level.h"
#include "engine.h"
#include <iostream>

PopupComponent::PopupComponent(Entity* const p, const sf::Vector2f& size, const std::string& text, unsigned int charSize)
    : Component(nullptr), _visible(false), _currentMode(Start) {

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

std::vector<std::shared_ptr<TowerButton>>& PopupComponent::getTowerButtons() {
    return _towerButtons;
}


void PopupComponent::update(double dt) {

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(Engine::GetWindow());
        if (isMouseOverCloseButton(mousePos)) {
            hide();
        }
    }

}

void PopupComponent::addTowerButton(std::shared_ptr<TowerButton> button) {
    std::cout << "added button to popup\n";
    _towerButtons.push_back(button);
}

void PopupComponent::setMode(PopupMode mode) {
    _currentMode = mode;
}


bool PopupComponent::isMouseOverCloseButton(const sf::Vector2i& mousePos) const {
    return _closeButton.getGlobalBounds().contains(sf::Vector2f(mousePos)); // Check if mouse position is within the button's bounds
}

void PopupComponent::setPosition(const sf::Vector2f& pos) {
    std::cout << "SET POPUP";
    _box.setPosition(pos);
    _text.setPosition(pos.x + 20.f, pos.y + 20.f); // Padding for the text

    // Close button position
    _closeButton.setPosition(pos.x + _box.getSize().x - _closeButton.getSize().x - 10.f, pos.y + _box.getSize().y - _closeButton.getSize().y - 10.f);
    _closeButtonText.setPosition(_closeButton.getPosition().x + 5.f, _closeButton.getPosition().y + 5.f);

    // Position tower buttons below the text area
    float towerButtonY = pos.y + 20.f + _text.getLocalBounds().height + 20.f; // Start below the text

    // Set positions for the tower buttons (make sure you reset positions first)
    std::cout << _towerButtons.size();
    auto index = 0;
    for (auto& button : _towerButtons) {
        std::cout << "POSITION OF TOWER\n";
        // Calculate button position relative to the popup's text
        sf::Vector2f popupPosition = getBoxPosition(); // Assuming PopupComponent provides a method to get its position
        sf::FloatRect textBounds = getTextBounds();    // Get the bounds of the text inside the popup

        float buttonX = popupPosition.x + textBounds.width + 30.f; // Place buttons to the right of the text
        float buttonY = popupPosition.y + textBounds.top + index * 35.f - 125.0f; // Adjust button's Y position for each tower

        button->setPosition(sf::Vector2f(sf::Vector2f(buttonX, buttonY))); // Position each button
        index++;
    }
}


bool PopupComponent::isMouseOverButton(const sf::RectangleShape& button) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(Engine::GetWindow());
    return button.getGlobalBounds().contains(sf::Vector2f(mousePos));  // Check if the mouse is over the button
}


void PopupComponent::renderTowerButtons() {
    // This function will render the dynamically created tower buttons
    // You could store the created buttons as an array and iterate over them to render
    for (auto& button : _towerButtons) {
        button->render(Engine::GetWindow());
    }
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

void PopupComponent::clearTowerButtons() {
    _towerButtons.clear();
    std::cout << "Cleared all tower buttons.\n";
}



bool PopupComponent::isVisible() const {
    return _visible;
}

void PopupComponent::render() {
    if (_visible) {

        Renderer::queue(&_box);
        Renderer::queue(&_text);
        Renderer::queue(&_closeButton);
        Renderer::queue(&_closeButtonText);

        if (_currentMode == ShopSystem) {
            renderTowerButtons();  // Render tower buttons when in shop system mode
        }




    }
}

void PopupComponent::createCloseButton() {
    _closeButton.setSize(sf::Vector2f(80.f, 40.f)); // Size of the button
    _closeButton.setFillColor(sf::Color(0, 0, 0, 180)); // Semi-transparent black background for the button
    _closeButton.setOutlineThickness(2.f);
    _closeButton.setOutlineColor(sf::Color::White);

    // Set up the text inside the button based on the current mode
    _closeButtonText.setFont(*_font);
    if (_currentMode == PopupMode::Start) {
        _closeButtonText.setString("Start");  // Text for the start screen
    }
    else if (_currentMode == PopupMode::ShopSystem) {
        _closeButtonText.setString("Continue");  // Text for the shop system
    }
    _closeButtonText.setCharacterSize(24);
    _closeButtonText.setFillColor(sf::Color::White);
}


sf::Vector2f PopupComponent::getBoxPosition() const {
    return _box.getPosition();
}

sf::FloatRect PopupComponent::getTextBounds() const {
    return _text.getGlobalBounds();
}



