#pragma once

#include <glm/vec3.hpp>

class AABB {
    public:
        // construct smallest rectangle that contains these points
        AABB(glm::vec3 p1, glm::vec3 p2);
        // construct rectangle at center with size
        AABB(glm::vec3 center, float w, float h, float d);
        // copy rectangle
        AABB(const AABB &rect);

        glm::vec3 getMin() const;
        glm::vec3 getMax() const;

    private:
        glm::vec3 min;
        glm::vec3 max;
};