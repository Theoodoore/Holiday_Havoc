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
#include "../components/cmp_shop_button.h"
#include <random>
#include <chrono>

using namespace std;
using namespace sf;


shared_ptr<Entity> enemy;
std::shared_ptr<PopupComponent> popup;
shared_ptr<Entity> hauntedHouse;
ShopSystem shopSystem(popup);  // Pass the existing 'popup' shared pointer

static std::shared_ptr<Tower> hoveringTower = nullptr; // For hover feedback

void LevelScene::Load() {
    ls::loadLevelFile("res/levels/maze.txt", 70.0f);
    cout << " Scene 1 Load" << endl;
    auto scaledWidth = ls::getWidth() * 70.0f;
    auto scaledHeight = ls::getHeight() * 80.0f;
    auto ho = Engine::getWindowSize().y - scaledHeight;
    auto wo = Engine::getWindowSize().x - scaledWidth;
    ls::setOffset(Vector2f(wo / 2.f, ho));

    // Create and configure the popup only once
    popup = makeEntity()->addComponent<PopupComponent>(
        sf::Vector2f(500.f, 250.f),
        "Welcome to Holiday Havoc!\nClick on a tile to place a tower\n\nStop Christmas from reaching\nyour Halloween mansion!",
        24
    );
    popup->setPosition(sf::Vector2f(Engine::getWindowSize().x / 2.f - 200, Engine::getWindowSize().y / 2.f - 75));
    popup->show(); // Show the popup immediately

    // Create and initialize the ShopSystem with the popup
    shopSystem = ShopSystem(popup);  // Pass the existing 'popup' shared pointer

    hauntedHouse = makeEntity();
    hauntedHouse->addComponent<HealthComponent>(100); // Assuming 100 is the max health
    sf::Vector2<size_t> endIndex = LevelSystem::findTiles(LevelSystem::END)[0];
    sf::Vector2f endPos = LevelSystem::getTilePosition(endIndex);
    hauntedHouse->addTag("hauntedHouse");
    hauntedHouse->setPosition(endPos);

    // Create 3 enemy entities
    for (int i = 0; i < 3; i++) {
        auto enemy = makeEntity();
        enemy->addComponent<TextureRenderComponent>("res/img/spritesheet.png");
        enemy->addComponent<HealthComponent>(100);

        // Offset each enemy's starting position
        sf::Vector2f startPos = LevelSystem::getTilePosition(LevelSystem::findTiles(LevelSystem::START)[0]);

        enemy->setPosition(startPos);

        enemy->addComponent<MovementComponent>(sf::Vector2f(-1.0f, 0.0f));
        enemy->addComponent<AttackComponent>(10, 1.5f, ents);

        auto sm = enemy->addComponent<StateMachineComponent>();
        sm->addState("stationary", make_shared<StationaryState>());
        sm->addState("roaming", make_shared<RoamingState>(enemy));
        sm->addState("rotating", make_shared<RotatingState>(enemy));
        sm->addState("attacking", make_shared<AttackingState>(enemy));

        // Create decision tree
        auto decision = make_shared<DistanceDecision>(
            endPos, 10.0f,
            make_shared<RoamingDecision>(), // If close to the START tile, roam towards it
            make_shared<RotatingDecision>(),
            make_shared<AtEndDecision>() // Otherwise, rotate
        );

        enemy->addComponent<DecisionTreeComponent>(decision);
    }


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
    auto shopButtonEntity = makeEntity()->addComponent<ShopButton>(
        spriteSheet,
        sf::Vector2f((windowSize.x / 2.f) - 50.f, windowSize.y - 180.f), // Position
        staticRect,
        hoverRect,
        clickRect,
        [this]() {
            shopSystem.displayShopItems(); // Action on click
        }
    );

    // Add towers to the shop system
    auto tower1 = std::make_shared<Tower>(this, sf::Vector2f(0.f, 0.f), 10, 100.f, 1.0f);
    auto tower2 = std::make_shared<Tower>(this, sf::Vector2f(0.f, 0.f), 15, 150.f, 1.5f);

    shopSystem.addTower(tower1, 100); // Price is 100 candy
    shopSystem.addTower(tower2, 150); // Price is 150 candy
}


void LevelScene::UnLoad() {
    cout << "Scene 1 Unload" << endl;

    ls::unload();
    Scene::UnLoad();

}

void LevelScene::Update(const double& dt) {
    if (popup->isVisible()) {
        popup->update(dt);
           
    }
    else {

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
