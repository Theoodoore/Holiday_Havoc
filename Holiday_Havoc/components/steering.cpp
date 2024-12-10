// steering.cpp
#include "steering.h"
#include <cmath> // for normalize
#include "../components/cmp_movement.h"

using namespace sf;

SteeringOutput Roaming::getSteering() const noexcept {
    SteeringOutput steering;

    // Move straight left (ignoring vertical target position)
    steering.direction = Vector2f(-1.0f, 0.0f);  // Always move left
              // Scale by max speed

    steering.rotation = 0.0f;  // No rotation in Roaming
    return steering;
}


SteeringOutput Rotating::getSteering() const noexcept {
    SteeringOutput steering;

    // Randomly decide between moving left, up, or down, but never right
    static bool initialized = false;

    if (!initialized) {
        std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed random generator
        initialized = true;
    }

    // Get the current direction from the MovementComponent of the owner
    auto currentDirection = _owner->get_components<MovementComponent>()[0]->getDirection();

    // Randomly decide between left (0), up (1), or down (2), but never right
    int direction = std::rand() % 3; // Generates 0 (left), 1 (up), or 2 (down)

    // Ensure the new direction is not the opposite of the current direction
    // Check for opposite directions
    switch (direction) {
    case 0: // Move left
        if (currentDirection.x > 0.0f) {
            direction = std::rand() % 2 + 1; // Re-roll for up or down
        }
        steering.direction = Vector2f(-1.0f, 0.0f);
        break;
    case 1: // Move up
        if (currentDirection.y > 0.0f) {
            direction = std::rand() % 2 + 1; // Re-roll for down if moving down
        }
        steering.direction = Vector2f(0.0f, -1.0f);
        break;
    case 2: // Move down
        if (currentDirection.y < 0.0f) {
            direction = std::rand() % 2; // Re-roll for up if moving up
        }
        steering.direction = Vector2f(0.0f, 1.0f);
        break;
    }

    steering.rotation = 0.0f;        // No rotation needed
    return steering;
}


