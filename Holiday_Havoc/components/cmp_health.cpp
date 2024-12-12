// cmp_health.cpp

#include "cmp_health.h"
#include "ecm.h"
#include <iostream>

HealthComponent::HealthComponent(Entity* p, int maxHealth)
    : Component(p), _maxHealth(maxHealth), _health(maxHealth), _alive(true) {}

void HealthComponent::update(double dt) {
    
}

void HealthComponent::takeDamage(int amount) {
    if (!_alive) return;

    _health -= amount;

    if (_health <= 0) {
        _health = 0;
        _alive = false;
        std::cout << "Entity defeated!\n";
        _parent->setForDelete();
    }
}


int HealthComponent::getHealth() const {
    return _health;
}

bool HealthComponent::isDefeated() const {
    return !_alive;
}
