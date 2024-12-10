// steering_decisions.h
#pragma once

#include <engine.h>
#include "../components/cmp_decision_tree.h"
#include "../components/cmp_state_machine.h"
#include "../components/cmp_movement.h"
#include "LevelSystem.h"
#include <iostream>


class DistanceDecision : public MultiDecision
{
private:
    sf::Vector2f _target;
    float _distance;



    // Check if the enemy's next position is blocked by a wall
    bool isPathBlocked(Entity* owner)
    {
        sf::Vector2f position = owner->getPosition();

        // For example, check if the next tile in the direction of movement is a wall
        auto direction = owner->get_components<MovementComponent>()[0]; // Access the first MovementComponent
        

        
        sf::Vector2f new_pos = position + direction->getDirection();; // Get direction from movement logic

        // Check if the new position is a wall (assuming `LevelSystem::getTileAt` is valid)
        if (LevelSystem::getTileAt(new_pos) == LevelSystem::WALL)
        {
            
            return true;
        }

        return false;
    }

public:
    DistanceDecision(sf::Vector2f target, float distance,
        std::shared_ptr<DecisionTreeNode> roamingNode,
        std::shared_ptr<DecisionTreeNode> rotatingNode,
        std::shared_ptr<DecisionTreeNode> attackingNode)
        : _target(target), _distance(distance),
        MultiDecision({ roamingNode, rotatingNode, attackingNode }) {}

protected:
    std::shared_ptr<DecisionTreeNode> getBranch(Entity* owner) final
    {

        sf::Vector2f position = owner->getPosition();
        float distanceToTarget = std::sqrt(std::pow(position.x - _target.x, 2) + std::pow(position.y - _target.y, 2));
        // If the enemy is close enough to the target and there are no walls in the way, roam
        if (isPathBlocked(owner))
        {

            return _childNodes[1];
             // Roam
        }
        else if (distanceToTarget <= _distance)
        {
            
            return _childNodes[2];  // Rotate (if path is blocked or distance is too far)
        }
        else {
            return _childNodes[0];

        }
    }

};


class StationaryDecision : public DecisionTreeNode
{
public:
    void makeDecision(Entity *owner) final {
        auto sm = owner->get_components<StateMachineComponent>();
        sm[0]->changeState("stationary");
    }
};

class RoamingDecision : public DecisionTreeNode
{
public:
    void makeDecision(Entity *owner) final {
        auto sm = owner->get_components<StateMachineComponent>();
        sm[0]->changeState("roaming");
    }
};

class RotatingDecision : public DecisionTreeNode
{
public:
    void makeDecision(Entity *owner) final {
        auto sm = owner->get_components<StateMachineComponent>();
        sm[0]->changeState("rotating");
    }
};

class AtEndDecision : public DecisionTreeNode {
public:
    void makeDecision(Entity* owner) final {
        auto sm = owner->get_components<StateMachineComponent>();
        sm[0]->changeState("attacking");
        
    }
};
