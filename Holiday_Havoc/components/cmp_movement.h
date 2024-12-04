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
    MovementComponent(Entity* parent, float initialSpeed);

    void setPathAStar(const sf::Vector2<size_t>& start, const sf::Vector2<size_t>& goal);
    void moveToNext(double dt);

    virtual void update(double dt) override;
    virtual void render() override {}
};
