// steering_states.cpp
#include "steering_states.h"
#include "../components/cmp_movement.h"
#include "levelsystem.h"

using namespace sf;

void StationaryState::execute(Entity* owner, double dt) noexcept {

}

void RoamingState::execute(Entity* owner, double dt) noexcept {
    

    // Get the movement direction from the MovementComponent
    auto direction = owner->get_components<MovementComponent>()[0]->getDirection();

    // Calculate the new position based on the direction and speed
    auto new_pos = owner->getPosition() + (direction * (float)dt * 100.0f);

    // Check for valid movement (no walls)
    if (LevelSystem::getTileAt(new_pos) == LevelSystem::WALL) {
        // Transition to RotatingState if a wall is detected
        owner->get_components<StateMachineComponent>()[0]->changeState("RotatingState");
    }
    else {
        // Continue roaming in the stored direction
        owner->setPosition(new_pos);
    }
}


void RotatingState::execute(Entity* owner, double dt) noexcept {

    // Rotating movement logic
    auto output = _steering.getSteering();
    
    auto new_pos = owner->getPosition() + (output.direction * (float)dt * 100.0f);

    // Check if a valid roaming direction is found
    if (LevelSystem::getTileAt(new_pos) != LevelSystem::WALL) {
        // Transition back to RoamingState
        
        owner->setPosition(new_pos);
        owner->get_components<MovementComponent>()[0]->setDirection(output.direction);
        owner->get_components<StateMachineComponent>()[0]->changeState("RoamingState");
    }

}


void AttackingState::execute(Entity* owner, double dt) noexcept {
    // Get the current time
    auto now = std::chrono::steady_clock::now();

    // Calculate the time since the last attack
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - lastAttackTime).count();

    if (elapsed >= 5) { // If 5 seconds or more have passed
        auto attackComp = owner->get_components<AttackComponent>()[0];
        attackComp->attack(); // Trigger attack logic
        lastAttackTime = now; // Reset the attack timer
    }

    auto sm = owner->get_components<StateMachineComponent>();
    auto position = owner->getPosition();
    sf::Vector2f endPosition = LevelSystem::getTilePosition(LevelSystem::findTiles(LevelSystem::END)[0]);

    // Check if the enemy is within a certain distance of the end position
    float distance = std::sqrt(std::pow(position.x - endPosition.x, 2) + std::pow(position.y - endPosition.y, 2));

    if (distance <= 1.0f) { // You can adjust the threshold for distance (e.g., 1.0f)
        sm[0]->changeState("attacking"); // Stay in AttackingState when close enough
    }
    else {
        sm[0]->changeState("roaming"); // Otherwise, roam towards the end
    }
}
