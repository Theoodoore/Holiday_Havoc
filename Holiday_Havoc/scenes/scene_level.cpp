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
#include "../components/cmp_basic_movement.h"
#include "../components/steering_states.h"
#include "../components/cmp_decision_tree.h"
#include "../components/cmp_state_machine.h"
#include "../components/steering_decisions.h"
#include <random>
#include <chrono>

using namespace std;
using namespace sf;

static std::shared_ptr<PopupComponent> popup;
shared_ptr<Entity> enemy;
shared_ptr<Entity> hauntedHouse;


void LevelScene::Load() {
  ls::loadLevelFile("res/levels/maze.txt", 70.0f);
  cout << " Scene 1 Load" << endl;


  auto scaledWidth = ls::getWidth() * 70.0f;
  auto scaledHeight = ls::getHeight() * 80.0f;

  auto ho = Engine::getWindowSize().y - scaledHeight;
  auto wo = Engine::getWindowSize().x - scaledWidth;

  ls::setOffset(Vector2f(wo / 2.f, ho));

  
  // Create and configure the popup
  popup = makeEntity()->addComponent<PopupComponent>(
      sf::Vector2f(500.f, 250.f),
      "Welcome to Holiday Havoc!\nClick on a tile to place a tower\n\nStop Christmas from reaching\nyour Halloween mansion!",
      24
  );
  popup->setPosition(sf::Vector2f(Engine::getWindowSize().x / 2.f - 200, Engine::getWindowSize().y / 2.f - 75));
  popup->show();

  hauntedHouse = makeEntity();
  hauntedHouse->addComponent<HealthComponent>(100); // Assuming 100 is the max health
  sf::Vector2<size_t> endIndex = LevelSystem::findTiles(LevelSystem::END)[0];
  sf::Vector2f endPos = LevelSystem::getTilePosition(endIndex);
  hauntedHouse->addTag("hauntedHouse");

  hauntedHouse->setPosition(endPos); 
 

  // Create enemy entity
  enemy = makeEntity();
  enemy->addComponent<TextureRenderComponent>("res/img/spritesheet.png");
  enemy->addComponent<HealthComponent>(100);
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
      make_shared<AtEndDecision>()// Otherwise, rotate
  );

  enemy->addComponent<DecisionTreeComponent>(decision);


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
    }
}

void LevelScene::Render() {
    // Render level system and entities
    ls::render(Engine::GetWindow());
    Scene::Render();

    // Render popup
    popup->render();
}
