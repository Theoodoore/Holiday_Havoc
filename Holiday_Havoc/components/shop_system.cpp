// shop_system.cpp

#include "shop_system.h"
#include "engine.h"
#include "system_resources.h"
#include <iostream>

ShopSystem::ShopSystem() : _selectedTower(nullptr), _shopVisible(false) {}

void ShopSystem::addTower(std::shared_ptr<Tower> tower, int price) {
    _availableTowers.emplace_back(tower, price);
}

void ShopSystem::displayShopItems(const sf::Vector2f& position) {
    if (!_shopVisible) return; // ONLY display if the shop is VISIBLE

    float offsetX = 50.f;
    float currentX = position.x + offsetX;

    for (const auto& towerPair : _availableTowers) {
        sf::Sprite towerSprite;
        towerSprite.setTexture(*Resources::get<sf::Texture>("res/img/spritesheet.png"));
        towerSprite.setTextureRect(sf::IntRect(0, 64, 16, 16));
        towerSprite.setScale(2.f, 2.f);
        towerSprite.setPosition(currentX, position.y - 50.f);

        Engine::GetWindow().draw(towerSprite);
        currentX += offsetX;
    }
}

void ShopSystem::toggleShopVisibility() {
    _shopVisible = !_shopVisible;
}

bool ShopSystem::isShopVisible() const {
    return _shopVisible;
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

std::shared_ptr<Tower> ShopSystem::getSelectedTower() const {
    return _selectedTower;
}

void ShopSystem::clearSelection() {
    _selectedTower = nullptr;
    std::cout << "Cleared tower selection.\n";
}

const std::vector<std::pair<std::shared_ptr<Tower>, int>>& ShopSystem::getAvailableTowers() const {
    return _availableTowers;
}
