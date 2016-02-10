#pragma once

class AABB;

#include <glm/vec3.hpp>

enum ShapeType {
    POINT = 0,
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