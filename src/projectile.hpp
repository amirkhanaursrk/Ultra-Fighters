#pragma once

#include "game_node.hpp"
#include "myglutils.h"
#include "physics_body.hpp"

#include <glm/vec3.hpp>

class Projectile: public GameNode {
    public:
        Projectile(GNPbody body);
        
        bool setup() override;
        void render(float interp) override;
        void update(double step) override;

    private:
        static GLuint vao;
        static GLuint program;

        double timeAlive = 0;
};