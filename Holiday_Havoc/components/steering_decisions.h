// steering_decisions.h
#pragma once

#include <engine.h>
#include "../components/cmp_decision_tree.h"
#include "../components/cmp_state_machine.h"
#include "../components/cmp_movement.h"
#include "LevelSystem.h"
#include <iostream>


class DistanceDecision : public Decision
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

protected:
    std::shared_ptr<DecisionTreeNode> getBranch(Entity* owner) final
    {


        // If the enemy is close enough to the target and there are no walls in the way, roam
        if (isPathBlocked(owner))
        {
            std::cout << "A WALL" << std::endl;
            return _falseNode;
             // Roam
        }
        else
        {
           // std::cout << "rotating" << std::endl;
            return _trueNode;  // Rotate (if path is blocked or distance is too far)
        }
    }

public:
    DistanceDecision(sf::Vector2f target, float distance, std::shared_ptr<DecisionTreeNode> trueNode, std::shared_ptr<DecisionTreeNode> falseNode)
        : _target(target), _distance(distance), Decision(trueNode, falseNode) { }
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