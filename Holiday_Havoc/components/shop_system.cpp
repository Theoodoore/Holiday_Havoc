#include "shop_system.h"
#include "../scenes/scene_level.h"
#include "../components/cmp_popup.h"
#include <iostream>
#include "ecm.h"
#include "engine.h"

ShopSystem::ShopSystem(std::shared_ptr<PopupComponent> popup)
    : _popup(popup), _selectedTower(nullptr) {}

void ShopSystem::addTower(std::shared_ptr<Tower> tower, int price) {
    _availableTowers.emplace_back(tower, price);
}

void ShopSystem::selectTower(int index) {
    std::cout << "SELECTING " << index << " for placement.\n";
    if (index > 0 && index <= _availableTowers.size()) {
        _selectedTower = _availableTowers[index - 1].first;
        _purchasedTowers.push_back(_selectedTower); // Mark tower as purchased
        std::cout << "Selected Tower " << index << " for placement.\n";
        updateShopButtons(); // Remove the corresponding button
    }
    else {
        std::cout << "Invalid selection.\n";
    }
}

void ShopSystem::displayShopItems() {
    std::cout << "Displaying available towers.\n";

    if (_popup) {
       
        updateShopButtons(); // Update only the remaining buttons
    }

    std::string towerList = "Available Towers:\n";
    for (size_t i = 0; i < _availableTowers.size(); ++i) {
        if (std::find(_purchasedTowers.begin(), _purchasedTowers.end(), _availableTowers[i].first) != _purchasedTowers.end()) {
            continue; // Skip already purchased towers
        }
        towerList += std::to_string(i + 1) + ": Tower (Price: " + std::to_string(_availableTowers[i].second) + " candy)\n";
    }

    if (_popup) {
        _popup->setMode(PopupComponent::ShopSystem);
        _popup->setText(towerList);
        _popup->setPosition(sf::Vector2f(200.f, 150.f));
        _popup->changeText();
        _popup->show();
    }
}

void ShopSystem::updateShopButtons() {
    if (_popup) {
        _popup->clearTowerButtons(); // Clear existing buttons
        for (size_t i = 0; i < _availableTowers.size(); ++i) {
           if (std::find(_purchasedTowers.begin(), _purchasedTowers.end(), _availableTowers[i].first) != _purchasedTowers.end()) {
               continue; // Skip purchased towers
            }
            createTowerButton(i); 
        }
    }
}

void ShopSystem::selectTowerForPlacement(std::shared_ptr<Tower> tower) {
    _selectedTower = tower;
    std::cout << "PURCHASED\n";
    _purchasedTowers.push_back(tower); // Mark the tower as purchased
    std::cout << "Selected Tower for placement.\n";
    _popup->hide();
}

void ShopSystem::createTowerButton(int index) {
    auto tower = _availableTowers[index].first;
    int price = _availableTowers[index].second;

    if (_popup) {
        sf::Vector2f popupPosition = _popup->getBoxPosition();
        sf::FloatRect textBounds = _popup->getTextBounds();

        float buttonX = popupPosition.x + textBounds.width + 70.f;
        float buttonY = popupPosition.y + textBounds.top + index * 60.f;

        auto button = std::make_shared<TowerButton>(tower, price, sf::Vector2f(buttonX, buttonY));
        button->setOnClickCallback([this, tower]() {
            selectTowerForPlacement(tower);
            });

        _popup->addTowerButton(button);
    }
}

std::shared_ptr<Tower> ShopSystem::getSelectedTower() const {
    return _selectedTower;
}

void ShopSystem::clearSelection() {
    _selectedTower = nullptr;
    std::cout << "Cleared tower selection.\n";
}
