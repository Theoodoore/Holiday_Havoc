// scene_menu.cpp
#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void MenuScene::Load() {
  cout << "Menu Load \n";
  {
    auto txt = makeEntity();
    auto t = txt->addComponent<TextComponent>(
        "Holiday Havoc\n\nPress Space to Start");
  }
  setLoaded(true);
}

void MenuScene::Update(const double& dt) {

  if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
    Engine::ChangeScene(&level);
  }

  Scene::Update(dt);
}
