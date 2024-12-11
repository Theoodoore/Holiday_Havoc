#include "shop_system.h"
#include <iostream>

ShopSystem::ShopSystem() : _selectedTower(nullptr) {}

void ShopSystem::addTower(std::shared_ptr<Tower> tower, int price) {
    _availableTowers.emplace_back(tower, price);
}

void ShopSystem::displayShopItems() {
    std::cout << "Available Towers:\n";
    for (size_t i = 0; i < _availableTowers.size(); ++i) {
        std::cout << i + 1 << ": Tower (Price: " << _availableTowers[i].second << " candy)\n";
    }
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
