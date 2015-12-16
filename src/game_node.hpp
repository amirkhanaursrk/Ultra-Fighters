#pragma once

#include "loop.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <vector>

class GameScene;

class GameNode: public LoopListener {
public:
    GameNode* parent = NULL;
    GameScene* scene = NULL;
    std::vector<GameNode*> children;

    void addChild(GameNode* child);
    void removeChild(GameNode* child);
    bool isSetup();
    void setSetup(bool didSetup);

protected:
    bool didSetup = false;
};