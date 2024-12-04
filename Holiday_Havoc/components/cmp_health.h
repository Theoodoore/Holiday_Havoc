#pragma once
#include <ecm.h>

class HealthComponent : public Component {
protected:
    int _health;
    int _maxHealth;
    bool _alive;

public:
    explicit HealthComponent(Entity* p, int maxHealth);
    HealthComponent() = delete;

    void takeDamage(int amount);
    int getHealth() const;
    bool isDefeated() const;

    void render() override {}
    void update(double dt) override;
};
