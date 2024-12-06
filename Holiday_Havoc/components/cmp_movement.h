#pragma once
#include "ecm.h"
#include "LevelSystem.h"
#include <vector>

class MovementComponent : public Component {
private:
    float speed;                       
    std::vector<sf::Vector2<size_t>> path;
    size_t currentTargetIndex;           

public:
    explicit MovementComponent(Entity* parent, float initialSpeed);
    MovementComponent() = delete;

    void setPath(const std::vector<sf::Vector2<size_t>>& newPath);
    void moveToNext(double dt);

    virtual void update(double dt) override;
    virtual void render() override {}

    ~MovementComponent() override = default;
};
