// scene_level.cpp

#include "scene_level.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include <random>
#include <chrono>
#include "../components/cmp_popup.h"

using namespace std;
using namespace sf;

static std::shared_ptr<PopupComponent> popup;
shared_ptr<Entity> enemy;
shared_ptr<Entity> hauntedHouse;
static ShopSystem shopSystem;
static std::shared_ptr<Tower> hoveringTower = nullptr; // Should work for hover stuff

void LevelScene::Load() {
    ls::loadLevelFile("res/levels/maze.txt", 70.0f);

    sf::Vector2u windowSize = Engine::GetWindow().getSize();

    // Load the sprite sheet
    sf::Texture* spriteSheet = new sf::Texture();
    if (!spriteSheet->loadFromFile("res/img/spritesheet.png")) {
        throw std::runtime_error("Failed to load sprite sheet!");
    }

    // Define shop button sprites
    sf::IntRect staticRect(0, 128, 30, 16);
    sf::IntRect hoverRect(32, 128, 30, 16);
    sf::IntRect clickRect(64, 128, 30, 16);

    // Init shop button
    shopButtonEntity = makeEntity();
    shopButtonEntity->addComponent<ShopButton>(
        spriteSheet,
        sf::Vector2f((windowSize.x / 2.f) - 50.f, windowSize.y - 180.f),
        staticRect,
        hoverRect,
        clickRect,
        [this]() {
            _showShopTowerSprite = !_showShopTowerSprite; // Make shop sprite visible
        }
    );

    // Initialize shop tower sprite
    if (!_shopTowerTexture.loadFromFile("res/img/spritesheet.png")) {
        throw std::runtime_error("Failed to load shop tower texture!");
    }
    _shopTowerSprite.setTexture(_shopTowerTexture);
    _shopTowerSprite.setTextureRect(sf::IntRect(0, 16, 16, 16));
    _shopTowerSprite.setScale(4.f, 4.f);
    _shopTowerSprite.setPosition((windowSize.x / 2.f) + 115.f, windowSize.y - 180.f);

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

    static bool wasMousePressed = false;
    bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    // Handle shop tower sprite click
    if (_showShopTowerSprite && _shopTowerSprite.getGlobalBounds().contains(mousePos)) {
        if (!wasMousePressed && isMousePressed) { // Mouse was clicked
            shopSystem.selectTower(1); // Select the tower
            std::cout << "Tower selected from shop" << std::endl;
        }
    }

    // Tower placement stuff
    if (shopSystem.getSelectedTower() && ls::isOnGrid(mousePos)) {
        auto tileIndex = ls::getTileIndexAt(mousePos);
        auto tilePos = ls::getTilePosition(tileIndex);

        if (!hoveringTower) {
            hoveringTower = shopSystem.getSelectedTower();
            if (hoveringTower) {
                hoveringTower->setHovering(true);
                hoveringTower->setPosition(tilePos);
            }
        } else {
            hoveringTower->setPosition(tilePos);

            // Place the tower (Not working!!)
            if (!wasMousePressed && isMousePressed) { // Mouse was clicked
                if (ls::getTile(tileIndex) == LevelSystem::EMPTY) { // Ensure the tile is empty
                    hoveringTower->setHovering(false);
                    ents.list.push_back(hoveringTower);
                    hoveringTower = nullptr;
                    shopSystem.clearSelection();
                    std::cout << "Tower placed on the grid" << std::endl;
                } else {
                    std::cout << "Cannot place tower here; tile is not empty." << std::endl;
                }
            }
        }
    } else if (hoveringTower) {
        hoveringTower->setHovering(false);
        hoveringTower = nullptr;
    }

    // Update mouse variable
    wasMousePressed = isMousePressed;
}





void LevelScene::Render() {
    // Render level system and entities
    ls::render(Engine::GetWindow());
    Scene::Render();

    // Render popup
    if (popup) {
        popup->render();
    }

    // Render the shop tower sprite if it's visible
    if (_showShopTowerSprite) {
        Engine::GetWindow().draw(_shopTowerSprite);
    }
}
