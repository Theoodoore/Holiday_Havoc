// tower.cpp

#include "tower.h"

Tower::Tower(Scene* scene, const sf::Vector2f& position, int damage, float range, float attackRate)
    : Entity(scene), _isHovering(false) {
    setPosition(position);
    _attackComponent = addComponent<AttackComponent>(damage, range, scene->ents);
    _textureComponent = addComponent<TextureRenderComponent>("assets/tower.png");
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
