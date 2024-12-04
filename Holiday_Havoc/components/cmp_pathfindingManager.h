// PathfindingManager.h
#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class PathfindingManager {
public:
    static std::vector<sf::Vector2<size_t>> findPathAStar(
        const sf::Vector2<size_t>& start,
        const sf::Vector2<size_t>& goal);
};
