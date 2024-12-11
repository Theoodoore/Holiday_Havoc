// tower.cpp

#include "tower.h"

Tower::Tower(Scene* scene, const sf::Vector2f& position, int damage, float range, float attackRate)
    : Entity(scene), _isHovering(false) {
    setPosition(position);
    _attackComponent = addComponent<AttackComponent>(damage, range, scene->ents);
    sf::IntRect textureRegion(0, 16, 16, 16);  // Define the texture region
    _textureComponent = addComponent<TextureRenderComponent>("res/img/spritesheet.png", textureRegion);
    _damage = damage;
}

void Tower::setHovering(bool hovering) {
    _isHovering = hovering;
    _textureComponent->setOpacity(hovering ? 128 : 255); // Semi-transparent for hover
}

void Tower::updateHoverPosition(const sf::Vector2f& position) {
    if (_isHovering) {
        setPosition(position);
    }
}

void Tower::update(double dt) {
    Entity::update(dt);
    // MAYBE: (Add logic for active towers if needed)
}

int Tower::getDamage() {
    return _damage;
}
