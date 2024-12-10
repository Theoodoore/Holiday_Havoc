#include "cmp_movement.h"

MovementComponent::MovementComponent(Entity* parent, sf::Vector2f direction)
    : Component(parent), _direction(direction) {}


void MovementComponent::setDirection(const sf::Vector2f& direction) {
    _direction = direction;
}

sf::Vector2f MovementComponent::getDirection() const {
    return _direction;
}

void MovementComponent::update(double dt) {
    // Optionally, implement any logic here for continuous movement or apply speed
    // For example, you could multiply the direction by a speed factor and apply time delta (dt)
}