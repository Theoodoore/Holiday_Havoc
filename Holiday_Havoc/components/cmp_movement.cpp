#include "cmp_movement.h"
#include "cmp_pathfindingManager.h"

MovementComponent::MovementComponent(Entity* parent, float initialSpeed)
    : Component(parent), speed(initialSpeed), currentTargetIndex(0) {}


void MovementComponent::setPathAStar(const sf::Vector2<size_t>& start, const sf::Vector2<size_t>& goal) {
    path = findPathAStar(
        start,
        goal,
        [](const sf::Vector2<size_t>& pos) {
            return LevelSystem::getTileAt(LevelSystem::getTilePosition(pos)) == LevelSystem::WALL;
        });
    currentTargetIndex = 0;
}

void MovementComponent::moveToNext(double dt) {
    if (currentTargetIndex >= path.size()) {
        return; // Path is complete
    }

    // Get the current position of the entity
    sf::Vector2f currentPosition = _parent->getPosition();

    // Check for obstacles dynamically
    sf::Vector2<size_t> currentTile = path[currentTargetIndex];
    if (LevelSystem::getTileAt(LevelSystem::getTilePosition(currentTile)) == LevelSystem::WALL) {
        // Recalculate path if blocked
        setPathAStar(LevelSystem::getTilePosition(currentPosition), path.back());
        return;
    }

    // Move logic remains the same
    sf::Vector2f targetPosition = ls::getTilePosition(currentTile);
    sf::Vector2f direction = targetPosition - currentPosition;
    float distanceToTarget = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distanceToTarget > 0) {
        direction /= distanceToTarget;
    }

    float step = speed * static_cast<float>(dt);
    if (distanceToTarget <= step) {
        _parent->setPosition(targetPosition);
        currentTargetIndex++;
    }
    else {
        _parent->setPosition(currentPosition + direction * step);
    }
}



void MovementComponent::update(double dt) {
    moveToNext(dt);
}

