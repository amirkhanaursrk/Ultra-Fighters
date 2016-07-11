#pragma once

#include "shape.hpp"
#include "aabb.hpp"

#include <glm/vec3.hpp>

class Sphere: public Shape {
    public:
        glm::vec3 center;

        Sphere(glm::vec3 center, float radius);
        Sphere(float radius): Sphere(glm::vec3(0, 0, 0), radius) {}
        Sphere(const Sphere &copy);
        Sphere(): Sphere(glm::vec3(0, 0, 0), 1) {}

        float getRadius() const;
        void setRadius(float radius);

        // Abstract methods for Shape

        bool containsPoint(glm::vec3 point) const override;
        AABB getBoundingBox() const override;
        ShapeType getType() const override;

    private:
        float radius;
};