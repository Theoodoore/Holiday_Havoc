#include "cmp_movement.h"

MovementComponent::MovementComponent(Entity* parent, float initialSpeed)
    : Component(parent), speed(initialSpeed), currentTargetIndex(0) {}

void MovementComponent::setPath(const std::vector<sf::Vector2<size_t>>& newPath) {
    path = newPath;
    currentTargetIndex = 0; // Start at the beginning of the new path
}

void MovementComponent::moveToNext(double dt) {
    if (currentTargetIndex >= path.size()) {
        return; // Path is complete
    }

    // Get the current position of the entity
    sf::Vector2f currentPosition = _parent->getPosition();

    // Get the target tile position
    sf::Vector2f targetPosition = ls::getTilePosition(path[currentTargetIndex]);

    // Calculate the direction vector
    sf::Vector2f direction = targetPosition - currentPosition;
    float distanceToTarget = sqrt(direction.x * direction.x + direction.y * direction.y);

    // Normalize the direction
    if (distanceToTarget > 0) {
        direction /= distanceToTarget;
    }

    // Move the entity closer to the target based on speed and time
    float step = speed * static_cast<float>(dt);
    if (distanceToTarget <= step) {
        _parent->setPosition(targetPosition); // Snap to the target
        currentTargetIndex++; // Advance to the next tile
    }
    else {
        _parent->setPosition(currentPosition + direction * step);
    }
}


void MovementComponent::update(double dt) {
    moveToNext(dt);
}

