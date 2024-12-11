#include "scene_level.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include "../components/cmp_popup.h"
#include "../components/cmp_texture_render.h"
#include "../components/cmp_movement.h"
#include "../components/cmp_health.h"
#include "../components/cmp_attack.h"
#include "../components/steering_states.h"
#include "../components/cmp_decision_tree.h"
#include "../components/cmp_state_machine.h"
#include "../components/steering_decisions.h"
#include "../components/shop_system.h" // Added this
#include "../components/Shop_Button.h"
#include <random>
#include <chrono>

using namespace std;
using namespace sf;

static std::shared_ptr<PopupComponent> popup;
shared_ptr<Entity> enemy;
shared_ptr<Entity> hauntedHouse;
static ShopSystem shopSystem; // Added ShopSystem
static std::shared_ptr<Tower> hoveringTower = nullptr; // For hover feedback

void LevelScene::Load() {
    ls::loadLevelFile("res/levels/maze.txt", 70.0f);

    sf::Vector2u windowSize = Engine::GetWindow().getSize();

    // Load the sprite sheet
    sf::Texture* spriteSheet = new sf::Texture();
    if (!spriteSheet->loadFromFile("res/img/spritesheet.png")) {
        throw std::runtime_error("Failed to load sprite sheet!");
    }

    // Define shop button states
    sf::IntRect staticRect(0, 128, 30, 16);
    sf::IntRect hoverRect(32, 128, 30, 16);
    sf::IntRect clickRect(64, 128, 30, 16);

    // Create shop button
    auto shopButtonEntity = makeEntity();
    shopButtonEntity->addComponent<ShopButton>(
        spriteSheet,
        sf::Vector2f((windowSize.x / 2.f) - 50.f, windowSize.y - 180.f), // Position
        staticRect,
        hoverRect,
        clickRect,
        [this]() {
            shopSystem.displayShopItems(); // Action on click
        }
    );

    // Initialize popup
    popup = makeEntity()->addComponent<PopupComponent>(
        sf::Vector2f(500.f, 250.f),
        "Welcome to Holiday Havoc!\nClick on a tile to place a tower\n\nStop Christmas from reaching\nyour Halloween mansion!",
        24
    );
    popup->setPosition(sf::Vector2f(windowSize.x / 2.f - 200, windowSize.y / 2.f - 75));
    popup->show();
}

void LevelScene::UnLoad() {
    cout << "Scene 1 Unload" << endl;

    ls::unload();
    Scene::UnLoad();
}

void LevelScene::Update(const double& dt) {
    // Handle popup visibility
    if (popup && popup->isVisible()) {
        popup->update(dt);
        return;
    }

    Scene::Update(dt);

    // Get mouse position
    sf::Vector2f mousePos = Engine::GetWindow().mapPixelToCoords(sf::Mouse::getPosition(Engine::GetWindow()));

    // Validate mouse position and ensure it's on the grid
    if (ls::isOnGrid(mousePos)) {
        try {
            auto tileIndex = ls::getTileIndexAt(mousePos); // Get the grid position (indices) of the tile
            auto tilePos = ls::getTilePosition(tileIndex); // Convert grid position to world position

            if (!hoveringTower) {
                // Create a hovering tower
                hoveringTower = shopSystem.getSelectedTower();
                if (hoveringTower) {
                    hoveringTower->setHovering(true);
                    hoveringTower->setPosition(tilePos);
                }
            }
            else {
                // Update hovering tower position
                hoveringTower->setPosition(tilePos);

                // Place the tower if the left mouse button is pressed
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    hoveringTower->setHovering(false); // Disable hover mode
                    ents.list.push_back(hoveringTower); // Add to entity manager
                    hoveringTower = nullptr; // Reset hovering tower
                    shopSystem.clearSelection(); // Clear selected tower
                }
            }
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    else {
        // Log mouse position if it's outside the grid bounds
        std::cerr << "Mouse position out of grid bounds: " << mousePos.x << ", " << mousePos.y << std::endl;

        if (hoveringTower) {
            // Clear hovering tower if mouse is off grid
            hoveringTower->setHovering(false);
            hoveringTower = nullptr;
        }
    }

    // Example: Press 1 or 2 to select a tower
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        shopSystem.selectTower(1); // Select the first tower
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        shopSystem.selectTower(2); // Select the second tower
    }
}


void LevelScene::Render() {
    // Render level system and entities
    ls::render(Engine::GetWindow());
    Scene::Render();

    // Render popup if it exists
    if (popup) {
        popup->render();
    }
    else {
        std::cerr << "Warning: popup is null in Render()" << std::endl;
    }
}
