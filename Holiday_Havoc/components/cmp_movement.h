// movement.h

#pragma once
#include <ecm.h>
#include <SFML/Graphics.hpp>

class MovementComponent : public Component {
protected:
    sf::Vector2f _direction;  // Direction of movement

public:
    explicit MovementComponent(Entity* parent, sf::Vector2f direction = { 0.f, 0.f });  // Default constructor
    void update(double) override;
    void render() override {}
    
    MovementComponent() = delete;
    void setDirection(const sf::Vector2f& direction);  // Set direction
    sf::Vector2f getDirection() const;  // Get current direction
};
