#include "game_node.hpp"

void GameNode::addChild(GameNode* child) {
    child->parent = this;
    child->scene = scene;
    children.push_back(child);
}

void GameNode::removeChild(GameNode* child) {
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
    child->parent = NULL;
}

bool GameNode::isSetup() {
    return didSetup;
}

void GameNode::setSetup(bool didSetup) {
    this->didSetup = didSetup;
}