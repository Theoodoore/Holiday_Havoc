#include "cmp_attack.h"
#include "cmp_health.h"
#include <cmath>
#include <iostream>

AttackComponent::AttackComponent(Entity* p, int damage, float range, EntityManager& entityManager)
    : Component(p), _damage(damage), _range(range), _entityManager(entityManager) {}

void AttackComponent::attack() {
    auto targets = getTargetsInRange();

    for (auto& target : targets) {
        auto healthComps = target->GetCompatibleComponent<HealthComponent>();
        if (!healthComps.empty()) {
            healthComps[0]->takeDamage(10);
        }
    }
}

std::vector<std::shared_ptr<Entity>> AttackComponent::getTargetsInRange() const {
    std::vector<std::shared_ptr<Entity>> targets;
    auto parentPos = _parent->getPosition();

    auto entities = _entityManager.list; 
    for (auto& entity : entities) {
        if (entity.get() == _parent) continue;

        auto targetPos = entity->getPosition();
        float distance = std::sqrt(std::pow(targetPos.x - parentPos.x, 2) +
            std::pow(targetPos.y - parentPos.y, 2));
        if (distance <= _range) {
            targets.push_back(entity);
        }
    }
    return targets;
}

void AttackComponent::setDamage(int damage) {
    _damage = damage;
}

void AttackComponent::setRange(float range) {
    _range = range;
}

int AttackComponent::getDamage() const {
    return _damage;
}

float AttackComponent::getRange() const {
    return _range;
}
