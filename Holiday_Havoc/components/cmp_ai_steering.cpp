#include "cmp_ai_steering.h"
#include "engine.h"
#include "steering.h"
#include "levelsystem.h"

using namespace sf;

void SteeringComponent::update(double dt) {
    // Get the START position from the level system
    auto end_tile = LevelSystem::findTiles(LevelSystem::END)[0];
    sf::Vector2f end_pos(static_cast<float>(end_tile.x), static_cast<float>(end_tile.y));

    // Calculate the vector toward the START tile
    auto to_end = normalize(end_pos - _parent->getPosition());

    // Attempt to move toward START
    auto new_pos = _parent->getPosition() + (to_end * (float)dt * _speed);

    // Check if the move is valid
    if (!validMove(new_pos)) {
        // If not valid, switch to rotating behavior
        auto rotate_output = _rotating.getSteering();
        move(rotate_output.direction * (float)dt);
    }
    else {
        // If valid, move toward START
        move(to_end * (float)dt * _speed);
    }
}

SteeringComponent::SteeringComponent(Entity* p)
    : _roaming(Roaming(p, sf::Vector2f(static_cast<float>(LevelSystem::findTiles(LevelSystem::END)[0].x),
        static_cast<float>(LevelSystem::findTiles(LevelSystem::END)[0].y)), 100.0f)),
    _rotating(Rotating(p, sf::Vector2f(static_cast<float>(LevelSystem::findTiles(LevelSystem::END)[0].x),
        static_cast<float>(LevelSystem::findTiles(LevelSystem::END)[0].y)), 100.0f)), Component(p), _speed(50.0f) {}

bool SteeringComponent::validMove(const sf::Vector2f& pos) const {
    // Check if the position is out of bounds
    if (pos.x < 0.0f || pos.x > Engine::GetWindow().getSize().x ||
        pos.y < 0.0f || pos.y > Engine::GetWindow().getSize().y) {
        return false;
    }

    // Check if the position would collide with a WALL tile
    auto tile = LevelSystem::getTileAt(pos);
    if (tile == LevelSystem::WALL) {
        return false;
    }

    // Otherwise, the move is valid
    return true;
}

void SteeringComponent::move(const sf::Vector2f& p) {
    auto new_pos = _parent->getPosition() + p;
    if (validMove(new_pos)) {
        _parent->setPosition(new_pos);
    }
}

void SteeringComponent::move(float x, float y) {
    move(Vector2f(x, y));
}


