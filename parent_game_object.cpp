#include "parent_game_object.hpp"

void ParentGameObject::setVPM(glm::mat4 VPM) {
    for (GameObject* child : children) {
        child->setVPM(VPM);
    }
    
    this->VPM = VPM;
}

void ParentGameObject::render(float interp) {
    for (GameObject* child : children) {
        child->render(interp);
    }
}

void ParentGameObject::update(double step) {
    if (newChildren.size() != 0) {
        for (GameObject* child: newChildren) {
            child->setup();
            child->setVPM(VPM);
            children.push_back(child);
        }
    
        newChildren.clear();
    }
    
    for (GameObject* child : children) {
        child->update(step);
    }
}

void ParentGameObject::addChild(GameObject* object) {
    if (object != NULL) {
        newChildren.push_back(object);
    }
}