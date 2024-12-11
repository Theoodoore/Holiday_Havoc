// tower.h

#pragma once
#include "ecm.h"
#include "cmp_attack.h"
#include "cmp_texture_render.h"
#include "engine.h"

class Tower : public Entity {
private:
    std::shared_ptr<AttackComponent> _attackComponent;
    std::shared_ptr<TextureRenderComponent> _textureComponent;
    bool _isHovering;

public:
    Tower(Scene* scene, const sf::Vector2f& position, int damage, float range, float attackRate);

    void setHovering(bool hovering);
    void updateHoverPosition(const sf::Vector2f& position);
    void update(double dt) override;
};
