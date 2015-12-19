#include "game_node.hpp"
#include "miscutils.hpp"

void GameNode::addChild(GameNode* child) {
    child->parent = this;
    child->scene = scene;
    newChildren.push_back(child);
}

void GameNode::removeChild(GameNode* child) {
    ezremove(children, child);
    ezremove(newChildren, child);
    oldChildren.push_back(child);
}