#include "cmp_pathfindingManager.h"
#include <queue>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include "LevelSystem.h"

// Add this hash definition for sf::Vector2<size_t>
namespace std {
    template <>
    struct hash<sf::Vector2<size_t>> {
        size_t operator()(const sf::Vector2<size_t>& v) const {
            return hash<size_t>()(v.x) ^ (hash<size_t>()(v.y) << 1);
        }
    };
}

std::vector<sf::Vector2<size_t>> PathfindingManager::findPathAStar(
    const sf::Vector2<size_t>& start,
    const sf::Vector2<size_t>& goal) {

    auto heuristic = [](const sf::Vector2<size_t>& a, const sf::Vector2<size_t>& b) {
        return std::abs(static_cast<int>(a.x) - static_cast<int>(b.x)) +
            std::abs(static_cast<int>(a.y) - static_cast<int>(b.y));
        };

    using Node = std::pair<int, sf::Vector2<size_t>>;
    std::priority_queue<Node, std::vector<Node>, std::greater<>> openSet;
    openSet.emplace(0, start);

    std::unordered_map<sf::Vector2<size_t>, sf::Vector2<size_t>> cameFrom;
    std::unordered_map<sf::Vector2<size_t>, int> costSoFar;
    costSoFar[start] = 0;

    const std::vector<sf::Vector2<int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

    while (!openSet.empty()) {
        sf::Vector2<size_t> current = openSet.top().second;
        openSet.pop();

        if (current == goal) {
            std::vector<sf::Vector2<size_t>> path;
            for (sf::Vector2<size_t> at = goal; at != start; at = cameFrom[at]) {
                path.push_back(at);
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const auto& dir : directions) {
            sf::Vector2<size_t> neighbor = {
                current.x + static_cast<size_t>(dir.x),
                current.y + static_cast<size_t>(dir.y)
            };

            if (neighbor.x < 0 || neighbor.y < 0 || LevelSystem::isWall(neighbor)) continue;

            int newCost = costSoFar[current] + 1;
            if (!costSoFar.count(neighbor) || newCost < costSoFar[neighbor]) {
                costSoFar[neighbor] = newCost;
                int priority = newCost + heuristic(neighbor, goal);
                openSet.emplace(priority, neighbor);
                cameFrom[neighbor] = current;
            }
        }
    }

    return {};
}
