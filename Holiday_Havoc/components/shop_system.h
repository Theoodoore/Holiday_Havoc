// shop_system.h

#pragma once
#include <string>
#include <vector>
#include <memory>
#include "tower.h"

class ShopSystem {
private:
    std::vector<std::pair<std::shared_ptr<Tower>, int>> _availableTowers;
    std::shared_ptr<Tower> _selectedTower;
    bool _shopVisible; // Keep track of if shop is visible

public:
    ShopSystem();

    void addTower(std::shared_ptr<Tower> tower, int price);
    void displayShopItems(const sf::Vector2f& position);
    void toggleShopVisibility(); // Toggle shop visibility
    bool isShopVisible() const;  // Get shop visibility
    void selectTower(int index);
    std::shared_ptr<Tower> getSelectedTower() const;
    void clearSelection();
    const std::vector<std::pair<std::shared_ptr<Tower>, int>>& getAvailableTowers() const; // Fixed return type
};
