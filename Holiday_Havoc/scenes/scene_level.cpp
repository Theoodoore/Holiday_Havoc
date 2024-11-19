#include "scene_level.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>

using namespace std;
using namespace sf;


void LevelScene::Load() {
  cout << " Scene 1 Load" << endl;

  auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  ls::setOffset(Vector2f(0, ho));

  cout << " Scene 1 Load Done" << endl;

  setLoaded(true);
}

void LevelScene::UnLoad() {
  cout << "Scene 1 Unload" << endl;

  ls::unload();
  Scene::UnLoad();
}

void LevelScene::Update(const double& dt) {

  Scene::Update(dt);
}

void LevelScene::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}
