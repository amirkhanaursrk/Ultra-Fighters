#pragma once

#include "aabb.hpp"
#include "sphere.hpp"
#include "miscutils.hpp"

inline bool intersects(const AABB &rectA, const AABB &rectB) {
    return
    rectA.getMax().x > rectB.getMin().x &&
    rectA.getMin().x < rectB.getMax().x &&
    rectA.getMax().y > rectB.getMin().y &&
    rectA.getMin().y < rectB.getMax().y &&
    rectA.getMax().z > rectB.getMin().z &&
    rectA.getMin().z < rectB.getMax().z;
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