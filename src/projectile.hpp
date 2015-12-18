#pragma once

#include "game_node.hpp"
#include "myglutils.h"

#include <glm/vec3.hpp>

class Projectile: public GameNode {
	public:
        Projectile(float x, float y, float z);

        bool setup() override;
        void render(float interp) override;
        void update(double step) override;

    private:
        static GLuint vao;
        static GLuint program;

        glm::vec3 pos;
};