#pragma once

#include "aabb.hpp"
#include "sphere.hpp"
#include "miscutils.hpp"

#include <glm/glm.hpp>

inline bool intersects(const AABB &rectA, const AABB &rectB) {
    return
    rectA.getMax().x > rectB.getMin().x &&
    rectA.getMin().x < rectB.getMax().x &&
    rectA.getMax().y > rectB.getMin().y &&
    rectA.getMin().y < rectB.getMax().y &&
    rectA.getMax().z > rectB.getMin().z &&
    rectA.getMin().z < rectB.getMax().z;
}

inline bool intersects(const Sphere &s1, const Sphere &s2) {
    glm::vec3 diff = s1.center - s2.center;
    float d2 = glm::dot(diff, diff);
    float rad = s1.getRadius() + s2.getRadius();

    return d2 >= SQR(rad);
}

inline bool intersects(const AABB &rect, const Sphere &sphere) {
    float r2 = SQR(sphere.getRadius());
    int dmin = 0;

    glm::vec3 c = sphere.center;
    glm::vec3 boxMin = rect.getMin();
    glm::vec3 boxMax = rect.getMax();
    
    for (int i = 0; i < 3; i++) {
        if (c[i] < boxMin[i]) dmin += SQR(c[i] - boxMin[i]);
        else if (c[i] > boxMax[i]) dmin += SQR(c[i] - boxMax[i]);
    }

    return dmin <= r2;
}

inline bool intersects(const Sphere &sphere, const AABB &rect) {
    return intersects(rect, sphere);
}