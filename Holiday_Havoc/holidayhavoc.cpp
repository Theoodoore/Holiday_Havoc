//pacman.cpp
#include "holidayhavoc.h"
#include "system_renderer.h"
#include "ecm.h"
#include <SFML/Graphics.hpp>
#include <iostream>

std::shared_ptr<Scene> gameScene;     // Definition of gameScene
std::shared_ptr<Scene> menuScene;     // Definition of menuScene
std::shared_ptr<Scene> activeScene;

void Scene::render() { 

        _ents.render(Renderer::getWindow()); // Call render with the window reference
    
}

void Scene::update(double dt) {

    for (const auto& entity : _ents.list) {
        if (entity) {
            entity->update(dt);
        }

    }

}


void MenuScene::update(double dt) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        activeScene = gameScene;
    }
    Scene::update(dt);

}

void MenuScene::render() {
	Renderer::queue(&text);
	Scene::render();
}

void MenuScene::load() {
	// Set up the text element
    font.loadFromFile("res/fonts/RobotoMono-Medium.ttf");
	text.setFont(font);
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::White);
	text.setString("Press Enter to Start");
	text.setPosition(100, 100); // Adjust position as needed
}

void GameScene::render() {
    Renderer::queue(&text);
    Scene::render();
}

void GameScene::load() {
    // Load the font for text (example)
    font.loadFromFile("res/fonts/RobotoMono-Medium.ttf");

    // Initialize the text for display
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setString("Game Scene");
    text.setPosition(10, 10); // Position on the screen
}


void GameScene::update(double dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
        activeScene = menuScene;
    }
    Scene::update(dt);


}
