#include "sphere.hpp"

#include <cmath>

Sphere::Sphere(glm::vec3 center, float radius) {
	this->center = center;
	this->radius = radius;
}

float Sphere::getRadius() const {
	return radius;
}

void Sphere::setRadius(float radius) {
	this->radius = std::fabs(radius);
}