#pragma once

#include "loop.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <vector>

class GameNode: public LoopListener {
public:
    GameNode* parent = NULL;
    std::vector<GameNode*> children;

    virtual void setCamPos(glm::vec3 pos) = 0;
    virtual void setVPM(glm::mat4 VPM) = 0;
    void addChild(GameNode* child);
    bool isSetup();
    void setSetup(bool didSetup);

protected:
    bool didSetup = false;
};