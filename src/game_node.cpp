#include "game_node.hpp"

void GameNode::addChild(GameNode* child) {
    child->parent = this;
    child->scene = scene;
    children.push_back(child);
}

bool GameNode::isSetup() {
    return didSetup;
}

void GameNode::setSetup(bool didSetup) {
    this->didSetup = didSetup;
}