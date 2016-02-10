#pragma once

#include "physics_body.hpp"
#include "game_node.hpp"

class GameNode;

template <typename T>
class GameNodePhysicsBody: public PhysicsBody<T> {
public:
	GameNode* node;

	GameNodePhysicsBody(GameNode* node) { this->node = node; }
    GameNodePhysicsBody(): GameNodePhysicsBody(NULL) {}
};

typedef GameNodePhysicsBody<float> GNPbody;

#include "game_node.hpp"