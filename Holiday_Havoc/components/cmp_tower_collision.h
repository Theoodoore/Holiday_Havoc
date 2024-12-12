// cmp_tower_collision

#pragma once
#include <ecm.h>

class TowerComponent : public Component {
public:
    explicit TowerComponent(Entity* p);
    void update(double dt) override;

private:
    void checkCollisions();
};
