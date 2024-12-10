#include "cmp_health.h"
#include <iostream>

HealthComponent::HealthComponent(Entity* p, int maxHealth)
    : Component(p), _maxHealth(maxHealth), _health(maxHealth), _alive(true) {}

void HealthComponent::update(double dt) {
    
}

void HealthComponent::takeDamage(int amount) {
    if (!_alive) return;
    std::cout << _health << std::endl;

    _health -= amount;

    std::cout << _health << std::endl;
    if (_health <= 0) {
        _health = 0;
        _alive = false;
        std::cout << "Entity defeated!\n";
    }
}

int HealthComponent::getHealth() const {
    return _health;
}

bool HealthComponent::isDefeated() const {
    return !_alive;
}
