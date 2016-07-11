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

// Shape Methods

bool Triangle::containsPoint(glm::vec3 point) const {
    return false; // figure out how to do this      @temp
}

AABB Triangle::getBoundingBox() const {
    glm::vec3 min, max;

    // x

    min.x = p1.x < p2.x ? p1.x : p2.x;
    min.x = min.x < p3.x ? min.x : p3.x;

    max.x = p1.x > p2.x ? p1.x : p2.x;
    max.x = max.x > p3.x ? max.x : p3.x;

    // y

    min.y = p1.y < p2.y ? p1.y : p2.y;
    min.y = min.y < p3.y ? min.y : p3.y;

    max.y = p1.y > p2.y ? p1.y : p2.y;
    max.y = max.y > p3.y ? max.y : p3.y;

    // z

    min.z = p1.z < p2.z ? p1.z : p2.z;
    min.z = min.z < p3.z ? min.z : p3.z;

    max.z = p1.z > p2.z ? p1.z : p2.z;
    max.z = max.z > p3.z ? max.z : p3.z;

    return AABB(min, max);
}

ShapeType Triangle::getType() const {
    return TRIANGLE;
}
