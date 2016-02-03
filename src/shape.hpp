#pragma once

#include "aabb.hpp"

#include <glm/vec3.hpp>

enum ShapeType {
    POINT,
    AABBOX,
    SPHERE,
    TRIANGLE,
};

class Shape {
public:
    virtual bool containsPoint(glm::vec3 point) const = 0;
    virtual AABB getBoundingBox() const = 0;
    virtual ShapeType getType() const = 0;
};