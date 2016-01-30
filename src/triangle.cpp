#include "triangle.hpp"

#include <glm/geometric.hpp>

Triangle::Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
}

glm::vec3 Triangle::n() const {
	return glm::normalize(glm::cross(p2 - p1, p3 - p1));
}