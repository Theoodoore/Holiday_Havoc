#include "shop_system.h"
#include "../scenes/scene_level.h"
#include "../components/cmp_popup.h"
#include <iostream>
#include "ecm.h"
#include "engine.h"

ShopSystem::ShopSystem(std::shared_ptr<PopupComponent> popup) : _popup(popup), _selectedTower(nullptr) {}

void ShopSystem::addTower(std::shared_ptr<Tower> tower, int price) {
    _availableTowers.emplace_back(tower, price);
}

void ShopSystem::selectTower(int index) {
    if (index > 0 && index <= _availableTowers.size()) {
        _selectedTower = _availableTowers[index - 1].first;
        std::cout << "Selected Tower " << index << " for placement.\n";
    }
    else {
        std::cout << "Invalid selection.\n";
    }
}

void ShopSystem::displayShopItems() {
    std::cout << "towers ";
    std::string towerList = "Available Towers:\n";
    for (size_t i = 0; i < _availableTowers.size(); ++i) {
        towerList += std::to_string(i + 1) + ": Tower (Price: " + std::to_string(_availableTowers[i].second) + " candy)\n";
        createTowerButton(i);  // Create a button for each tower
    }

    if (_popup) {
        std::cout << "Displaying towers in popup.\n";
        _popup->setText(towerList);  // Change button text to "Continue"
        _popup->setPosition(sf::Vector2f(200.f, 150.f));  // Example call to position the popup
        _popup->setMode(PopupComponent::ShopSystem);  // Set the popup mode to ShopSystem
        _popup->show();
    }
}

void ShopSystem::createTowerButton(int index) {
    auto tower = _availableTowers[index].first;
    int price = _availableTowers[index].second;

    if (_popup) {
        // Calculate button position relative to the popup's text
        sf::Vector2f popupPosition = _popup->getBoxPosition(); // Assuming PopupComponent provides a method to get its position
        sf::FloatRect textBounds = _popup->getTextBounds();    // Get the bounds of the text inside the popup

        float buttonX = popupPosition.x + textBounds.width + 70.f; // Place buttons to the right of the text
        float buttonY = popupPosition.y + textBounds.top + index * 60.f; // Adjust button's Y position for each tower

        auto button = std::make_shared<TowerButton>(tower, price, sf::Vector2f(buttonX, buttonY));
        _popup->addTowerButton(button); // Add button to the popup
    }
}


std::shared_ptr<Tower> ShopSystem::getSelectedTower() const {
    return _selectedTower;
}

void ShopSystem::clearSelection() {
    _selectedTower = nullptr;
    std::cout << "Cleared tower selection.\n";
}
