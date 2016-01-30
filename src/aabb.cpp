#include "aabb.hpp"
#include "intersect.hpp"

#include <cmath>

// Constructors

AABB::AABB(glm::vec3 p1, glm::vec3 p2) {
    for (int i = 0; i < 3; i++) {
        if (p1[i] < p2[i]) {
            min[i] = p1[i];
            max[i] = p2[i];
        }
        else {
            min[i] = p2[i];
            max[i] = p1[i];
        }
    }
}

AABB::AABB(glm::vec3 center, float w, float h, float d) {
    glm::vec3 halfSize = glm::vec3(w, h, d) / 2.0f;
    min = center - halfSize;
    max = center + halfSize;
}

AABB::AABB(const AABB &copy) {
    min = copy.getMin();
    max = copy.getMax();
}

// Public Methods

glm::vec3 AABB::getMin() const {
    return min;
}

glm::vec3 AABB::getMax() const{
    return max;
}

void AABB::centerAt(glm::vec3 center) {
    glm::vec3 halfSize = (max - min) / 2.0f;
    min = center - halfSize;
    max = center + halfSize;
}
