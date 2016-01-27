#pragma once

#include "aabb.hpp"
#include "game_node.hpp"
#include "game_scene.hpp"
#include "myglutils.h"

#include <glm/vec3.hpp>

class AABBTestNode: public GameNode {
    public:
    	AABBTestNode(glm::vec3 pos);
    	AABBTestNode(): AABBTestNode(glm::vec3(0, 2.0, 0)) {} // 2.0 because of default map @temp

        bool setup() override;
        void render(float interp) override;
        void update(double step) override;

    private:
        GLuint vao;
        GLuint program;

        glm::vec3 pos;
        AABB frame;
};