// cmp_ai_steering.h
#pragma once
#include <ecm.h>
#include "steering.h"

class SteeringComponent : public Component {
protected:
    Rotating _rotating; // Handles rotation to find a new direction
    Roaming _roaming;   // Handles moving straight ahead
    float _speed;
    bool validMove(const sf::Vector2f&) const; // Check if the move is valid

public:
    void update(double) override; // Update component state
    void move(const sf::Vector2f&); // Move entity
    void move(float x, float y);    // Overloaded move method
    void render() override { }     // No rendering needed for steering
    explicit SteeringComponent(Entity* p);
    SteeringComponent() = delete;
};
