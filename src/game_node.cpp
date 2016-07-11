#include "game_node.hpp"
#include "logger.h"
#include "miscutils.hpp"

void GameNode::addChild(GameNode* child) {
    if (child->parent != NULL) {
        log_msg(LOG_WARNING, "Node %s cannot be added to %s because it already has parent %s", child->name, this->name, child->parent->name);
        return;
    }

    child->parent = this;
    child->scene = scene;
    newChildren.push_back(child);
}

void GameNode::removeChild(GameNode* child) {
    ezremove(children, child);
    ezremove(newChildren, child);
    oldChildren.push_back(child);
}