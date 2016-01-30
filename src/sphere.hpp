#pragma once

#include <glm/vec3.hpp>

class Sphere {
	public:
		glm::vec3 center;

		Sphere(glm::vec3 center, float radius);
        Sphere(float radius): Sphere(glm::vec3(0, 0, 0), radius) {}
        Sphere(const Sphere &copy);
        Sphere(): Sphere(glm::vec3(0, 0, 0), 1) {}

        float getRadius() const;
        void setRadius(float radius);

        bool containsPoint(glm::vec3 pt) const;

    private:
        float radius;
};