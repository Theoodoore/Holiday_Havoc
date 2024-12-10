#include "steering_states.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_movement.h"
#include "levelsystem.h"

using namespace sf;

void StationaryState::execute(Entity* owner, double dt) noexcept {

}

void RoamingState::execute(Entity* owner, double dt) noexcept {
    std::cout << "ROAMING" << std::endl;

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

    std::cout << "ROTATING" << std::endl;
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
