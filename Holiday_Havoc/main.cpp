// main.cpp
#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"
#include "scenes/scene_level.h"

using namespace std;

MenuScene menu;
LevelScene level;

int main() {
	Engine::Start(1280, 720, "Platformer", &menu);
}