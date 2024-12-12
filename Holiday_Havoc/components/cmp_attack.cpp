// cmp_attack.cpp

#include "cmp_attack.h"
#include "cmp_health.h"
#include "ecm.h"
#include <cmath>
#include <iostream>
#include "engine.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>

AttackComponent::AttackComponent(Entity* p, int damage, float range, EntityManager& entityManager)
    : Component(p), _damage(damage), _range(range), _entityManager(entityManager) {}

void AttackComponent::attackEnemies() {
    auto targets = getTargetsInRange();

    for (auto& target : targets) {
        auto healthComps = target->GetCompatibleComponent<HealthComponent>();
        if (!healthComps.empty()) {
            healthComps[0]->takeDamage(10);
        }
    }
}

void AttackComponent::attack() {
    auto hauntedHouses = _parent->scene->ents.find("hauntedHouse");
   
    if (!hauntedHouses.empty()) {
        // Attack logic on the first hauntedHouse found
        auto hauntedHouse = hauntedHouses[0];  // Assuming you want to attack the first one found
        auto healthComp = hauntedHouse->get_components<HealthComponent>();
        if (!healthComp.empty()) {
            
            healthComp[0]->takeDamage(10); // Attack damage
        }
    }
}


std::vector<std::shared_ptr<Entity>> AttackComponent::getTargetsInRange() const {
    std::vector<std::shared_ptr<Entity>> targets;
    auto parentPos = _parent->getPosition();

    for (auto& entity : _entityManager.list) {
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
