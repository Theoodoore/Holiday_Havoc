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
	sf::Texture* titleScreenTexture = new sf::Texture();
    if (!titleScreenTexture->loadFromFile("res/img/title_screen.png")) {
		throw std::runtime_error("Failed to load title screen texture!");
    }
	sf::Sprite titleScreenSprite;
	titleScreenSprite.setTexture(*titleScreenTexture);
	
	Vector2u textureSize = titleScreenTexture->getSize();
	titleScreenSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
	
    //auto txt = makeEntity();
    //auto t = txt->addComponent<TextComponent>(
    //    "Holiday Havoc\n\nPress Space to Start");
	}
	setLoaded(true);
}

void MenuScene::Update(const double& dt) {

  if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
    Engine::ChangeScene(&level);
  }

  Scene::Update(dt);
}
