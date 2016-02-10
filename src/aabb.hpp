#pragma once

#include "shape.hpp"

#include <glm/vec3.hpp>

// A class for an Axis Aligned Bounding Box, or AABB for short
class AABB: public Shape {
public:
    // construct smallest rectangle that contains these points
    AABB(glm::vec3 p1, glm::vec3 p2);
    // construct rectangle at center with size
    AABB(glm::vec3 center, float w, float h, float d);
    // construct empty rectangle
    AABB(): AABB(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)) {}
    // copy rectangle
    AABB(const AABB &copy);

    glm::vec3 getMin() const;
    glm::vec3 getMax() const;

    void centerAt(glm::vec3 center);

    // Abstract methods for Shape

    bool containsPoint(glm::vec3 point) const override;
    AABB getBoundingBox() const override;
    ShapeType getType() const override;

private:
    glm::vec3 min;
    glm::vec3 max;
};