// cmp_movement.cpp
#include "cmp_movement.h"

MovementComponent::MovementComponent(Entity* parent, sf::Vector2f direction)
    : Component(parent), _direction(direction) {}


void MovementComponent::setDirection(const sf::Vector2f& direction) {
    _direction = direction;
}

sf::Vector2f MovementComponent::getDirection() const {
    return _direction;
}

void MovementComponent::update(double dt) {}