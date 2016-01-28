#include "sphere.hpp"

#include <cmath>

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