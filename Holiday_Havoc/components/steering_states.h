//steering_states.h
#pragma once

#include "steering.h"
#include "../components/cmp_state_machine.h"
#include "LevelSystem.h"


class StationaryState : public State
{
public:
    StationaryState() = default;
    void execute(Entity*, double) noexcept override;
};

class RoamingState : public State {
private:
    Roaming _steering;

public:
    RoamingState(std::shared_ptr<Entity> owner)
        : _steering(owner.get(),
            sf::Vector2f(static_cast<float>(LevelSystem::findTiles(LevelSystem::START)[0].x),
                static_cast<float>(LevelSystem::findTiles(LevelSystem::START)[0].y)),
            200.0f) {}

    void execute(Entity*, double) noexcept override;
};

class RotatingState : public State {
private:
    Rotating _steering;

public:
    RotatingState(std::shared_ptr<Entity> owner)
        : _steering(owner.get(),
            sf::Vector2f(static_cast<float>(LevelSystem::findTiles(LevelSystem::START)[0].x),
                static_cast<float>(LevelSystem::findTiles(LevelSystem::START)[0].y)),
            200.0f) {}

    void execute(Entity*, double) noexcept override;
};
