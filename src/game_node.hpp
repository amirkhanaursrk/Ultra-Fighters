#pragma once

#include "loop.hpp"
#include "logger.h" // @temp

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <vector>

class GameScene;

class GameNode: public LoopListener {
    public:
        GameNode* parent = NULL;
        GameScene* scene = NULL;
        std::vector<GameNode*> children;
        std::vector<GameNode*> newChildren;
        std::vector<GameNode*> oldChildren;

        virtual bool setup() = 0;
        virtual ~GameNode() {};

        void addChild(GameNode* child);
        void removeChild(GameNode* child);
};