#pragma once

#include "game_node.hpp"
#include "sphere.hpp"
#include "myglutils.h"

#include <glm/vec3.hpp>

class SphereNode: public GameNode {
    public:
        SphereNode(glm::vec3 center, float radius, unsigned char recLevel);
        SphereNode(glm::vec3 center, float radius);
        SphereNode(float radius);
        SphereNode();

        Sphere getSphere() const;

        bool setup() override;
        void render(float interp) override;
        void update(double step) override {}

    private:
        Sphere sphere;
        GLuint vao;
        GLuint program;
        int numVertices;

        unsigned char recLevel;
};