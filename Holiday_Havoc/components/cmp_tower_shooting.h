#pragma once

#include "ecm.h"
#include <SFML/System/Vector2.hpp>
#include <memory>

class TowerShootingComponent : public Component {
private:
    float _cooldown;                // Time between shots
    float _timeSinceLastShot;       // Timer for the cooldown
    float _range;                   // Range of the tower
    int _damage;                    // Damage dealt per shot
    std::shared_ptr<Entity> _target; // Current target entity

    void findClosestEnemy();        // Finds the closest enemy within range
    void shootAtTarget();           // Shoots a projectile at the current target

public:
    TowerShootingComponent(Entity* p, float cooldown, float range, int damage);

    void update(double dt) override;
    void render() override {}
};
