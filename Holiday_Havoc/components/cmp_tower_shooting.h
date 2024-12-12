/*
#pragma once

#include "ecm.h"
#include <SFML/System/Vector2.hpp>
#include <memory>

class TowerShootingComponent : public Component {
private:
    float _cooldown;                
    float _timeSinceLastShot;       
    float _range;                   
    int _damage;                    
    std::shared_ptr<Entity> _target; 

    void findClosestEnemy();        
    void shootAtTarget();           

public:
    TowerShootingComponent(Entity* p, float cooldown, float range, int damage);

    void update(double dt) override;
    void render() override {}
};
*/

// NO LONGER IN USE - theo
