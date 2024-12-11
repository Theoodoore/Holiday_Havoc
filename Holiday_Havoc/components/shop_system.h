#pragma once
#include <string>
#include <vector>
#include <memory>
#include "tower.h"
#include "../components/cmp_popup.h"

class ShopSystem {
private:
    // List of available towers and their prices
    std::vector<std::pair<std::shared_ptr<Tower>, int>> _availableTowers;
    std::vector<std::shared_ptr<Tower>> _purchasedTowers;


    // Currently selected tower type
    std::shared_ptr<Tower> _selectedTower;

    std::shared_ptr<PopupComponent> _popup;

public:
    ShopSystem(std::shared_ptr<PopupComponent> popup);

    // Add a tower to the shop with its price
    void addTower(std::shared_ptr<Tower> tower, int price);

    // Display the available items in the shop
    void displayShopItems();

    void ShopSystem::updateShopButtons();

    void createTowerButton(int index);

    // Select a tower for placement
    void selectTower(int index);

    // Get the currently selected tower
    std::shared_ptr<Tower> getSelectedTower() const;

    void selectTowerForPlacement(std::shared_ptr<Tower> tower);

    // Clear the current selection
    void clearSelection();
};