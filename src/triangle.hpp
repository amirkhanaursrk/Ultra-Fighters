#pragma once

#include "shape.hpp"
#include "aabb.hpp"

#include <glm/vec3.hpp>

class Triangle: public Shape {
    public:
        glm::vec3 p1, p2, p3;

        Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
        Triangle() : Triangle(glm::vec3(0, 1, 0), glm::vec3(-1, 0, 0), glm::vec3(1, 0, 0)) {}

        glm::vec3 n() const;

        // Shape methods

        bool containsPoint(glm::vec3 point) const override;
        AABB getBoundingBox() const override;
        ShapeType getType() const override;
};