#pragma once

#include <glm/vec3.hpp>

class Triangle {
    public:
        glm::vec3 p1, p2, p3;

        Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
        Triangle() : Triangle(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)) {}

        glm::vec3 n() const;
};