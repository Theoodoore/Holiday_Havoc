#include "cmp_texture_render.h"
#include "LevelSystem.h"
#include "engine.h"
#include <iostream>

TextureRenderComponent::TextureRenderComponent(Entity* p, const std::string& texturePath)
    : Component(p) {

   
    auto startTiles = LevelSystem::findTiles(LevelSystem::START);
    if (!startTiles.empty()) {
       
        auto startPosition = LevelSystem::getTilePosition(startTiles[0]);

        // Adjust for the center of the tile
        const float tileSize = 32.f; // Assuming tiles are 32x32
        startPosition += sf::Vector2f(tileSize, tileSize); // Center the sprite on the tile

        _parent->setPosition(startPosition);  // Set the sprite position

        std::cout << "Sprite positioned at START tile: ("
            << startPosition.x << ", " << startPosition.y << ")"
            << std::endl;
    }
    else {
        std::cerr << "No START tile found!" << std::endl;
    }

    setTexture(texturePath);
}

void TextureRenderComponent::setTexture(const std::string& texturePath) {
    if (_texture.loadFromFile(texturePath)) {
        _sprite.setTexture(_texture);

        _sprite.setTextureRect(sf::IntRect(0, 16, 16, 16)); 

        _sprite.setOrigin(8.f, 8.f);  

        _sprite.setScale(5.0f, 5.0f);

        std::cout << "Texture loaded successfully: " << texturePath << std::endl;
    }
    else {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
    }
}

void TextureRenderComponent::update(double dt) {
    _sprite.setPosition(_parent->getPosition());
    draw(Engine::GetWindow());
}

void TextureRenderComponent::draw(sf::RenderWindow& window) const {
    window.draw(_sprite);
}

void TextureRenderComponent::render() {
    draw(Engine::GetWindow());
}
