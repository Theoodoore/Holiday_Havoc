#pragma once
#include <ecm.h>
#include <vector>

class AttackComponent : public Component {
protected:
    int _damage;
    float _range;
    EntityManager& _entityManager; 

    std::vector<std::shared_ptr<Entity>> getTargetsInRange() const;


public:
    explicit AttackComponent(Entity* p, int damage, float range, EntityManager& entityManager);
    AttackComponent() = delete;

    void attack();
    void setDamage(int damage);
    void setRange(float range);
    int getDamage() const;
    float getRange() const;

    void render() override {}
    void update(double dt) override {}
};
