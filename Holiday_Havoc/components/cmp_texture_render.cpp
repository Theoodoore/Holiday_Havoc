#include "cmp_texture_render.h"
#include <iostream>

TextureRenderComponent::TextureRenderComponent(Entity* p, const std::string& texturePath)
    : Component(p) {
    if (!_texture.loadFromFile(texturePath)) {
        std::cerr << "Error loading texture: " << texturePath << "\n";
    }
    _sprite.setTexture(_texture);
}

void TextureRenderComponent::setTexture(const std::string& texturePath) {
    if (_texture.loadFromFile(texturePath)) {
        _sprite.setTexture(_texture);
    } else {
        std::cerr << "Error loading texture: " << texturePath << "\n";
    }
}

void TextureRenderComponent::update(double dt) {
    // Sync sprite's position to the parent entity's position
    _sprite.setPosition(_parent->getPosition());
}

void TextureRenderComponent::draw(sf::RenderWindow& window) const {
    window.draw(_sprite);
}

void TextureRenderComponent::render() {
    // Optionally overridden for additional rendering logic if needed
}
