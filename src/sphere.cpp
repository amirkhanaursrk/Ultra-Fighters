#include "sphere.hpp"
#include "miscutils.hpp"

#include <cmath>
#include <glm/geometric.hpp>

// Constructors

Sphere::Sphere(glm::vec3 center, float radius) {
	this->center = center;
	this->radius = radius;
}

Sphere::Sphere(const Sphere &copy) {
    this->center = copy.center;
    this->radius = copy.getRadius();
}

// Public Methods

float Sphere::getRadius() const {
	return radius;
}

void Sphere::setRadius(float radius) {
	this->radius = std::fabs(radius);
}

// Shape Methods

bool Sphere::containsPoint(glm::vec3 point) const {
    glm::vec3 diff = point - center;
    float dist2 = glm::dot(diff, diff);

    return dist2 < SQR(radius);
}

AABB Sphere::getBoundingBox() const {
    return AABB(center, radius, radius, radius);
}

ShapeType Sphere::getType() const {
    return SPHERE;
}