#include "scene_level.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include "../components/cmp_popup.h"

using namespace std;
using namespace sf;

static std::shared_ptr<PopupComponent> popup;


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
  
  cout << " Scene 1 Load Done" << endl;

  setLoaded(true);
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
        // Update the rest of the scene
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
