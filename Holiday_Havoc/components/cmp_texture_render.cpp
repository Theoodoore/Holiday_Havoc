// cmp_texture_render.cpp
#include "cmp_texture_render.h"
#include "LevelSystem.h"
#include "engine.h"
#include <iostream>

TextureRenderComponent::TextureRenderComponent(Entity* p, const std::string& texturePath, const sf::IntRect& textureRect)
    : Component(p) {

    // Set up position based on START tile
    auto startTiles = LevelSystem::findTiles(LevelSystem::START);
    if (!startTiles.empty()) {
        auto startPosition = LevelSystem::getTilePosition(startTiles[0]);

        // Adjust for the center of the tile
        const float tileSize = 32.f; // Assuming tiles are 32x32
        startPosition += sf::Vector2f(tileSize, tileSize); // Center the sprite on the tile

        _parent->setPosition(startPosition);  // Set the sprite position

        std::cout << "Sprite positioned at START tile: (" << startPosition.x << ", " << startPosition.y << ")\n";
    }
    else {
        std::cerr << "No START tile found!" << std::endl;
    }

    setTexture(texturePath, textureRect);  // Pass the texture rect to the function
}

void TextureRenderComponent::setTexture(const std::string& texturePath, const sf::IntRect& textureRect) {
    if (_texture.loadFromFile(texturePath)) {
        _sprite.setTexture(_texture);

        // Use the passed texture rectangle instead of a hardcoded value
        _sprite.setTextureRect(textureRect);

        _sprite.setOrigin(8.f, 8.f);  // Set origin to the center (for example)
        _sprite.setScale(5.0f, 5.0f);  // Scale the sprite

        std::cout << "Texture loaded successfully: " << texturePath << std::endl;
    }
    else {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
    }
}

void TextureRenderComponent::setOpacity(sf::Uint8 opacity) {
    sf::Color color = _sprite.getColor();
    color.a = opacity;  // Modify the alpha channel
    _sprite.setColor(color);
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
