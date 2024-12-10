// steering.h
#pragma once
#include <engine.h>

struct SteeringOutput {
    sf::Vector2f direction;
    float rotation;
};

class SteeringBehaviour {
public:
    virtual ~SteeringBehaviour() = default;
    virtual SteeringOutput getSteering() const noexcept = 0;
};

class Roaming : public SteeringBehaviour {
private:
    Entity* _owner;       // The entity performing the steering
    sf::Vector2f _target;     // Target position (START tile)
    float _maxSpeed;

public:
    Roaming() = delete;
    Roaming(Entity* owner, sf::Vector2f target, float maxSpeed)
        : _owner(owner), _target(target), _maxSpeed(maxSpeed) {}

    SteeringOutput getSteering() const noexcept override;
};

class Rotating : public SteeringBehaviour {
private:
    Entity* _owner;       // The entity performing the steering
    sf::Vector2f _target;     // Target position (START tile)
    float _maxSpeed;

public:
    Rotating() = delete;
    Rotating(Entity* owner, sf::Vector2f target, float maxSpeed)
        : _owner(owner), _target(target), _maxSpeed(maxSpeed) {}

    SteeringOutput getSteering() const noexcept override;
};
