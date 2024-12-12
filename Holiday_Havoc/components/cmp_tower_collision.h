// cmp_tower_collision.h

#pragma once
#include "ecm.h"

class TowerCollisionComponent : public Component {
protected:
    int _damage;

public:
    explicit TowerCollisionComponent(Entity* p, int damage);
    void update(double dt) override;
    void render() override {}
};