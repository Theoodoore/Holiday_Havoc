#pragma once
#include "ecm.h"
#include "cmp_attack.h"
#include "cmp_texture_render.h"
#include "engine.h"

class Tower : public Entity {
private:
	std::shared_ptr<AttackComponent> _attackComponent;

public:
	Tower(Scene* scene, const sf::Vector2f& position, int damage, float range, float attackRate);

	void update(double dt) override;
};