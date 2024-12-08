#include "Tower.h"

Tower::Tower(Scene* scene, const sf::Vector2f& position, int damage, float range, float attackRate)
	: Entity(scene) {
	setPosition(position);

	_attackComponent = addComponent<AttackComponent>(damage, range, scene->ents);

	// Need to add tower texture
	// Also need to implement an upgrade class
}

void Tower::update(double dt) {
	Entity::update(dt);

	if (_attackComponent) {
		_attackComponent->attack();
	}
}