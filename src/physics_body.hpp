#pragma once

#include "shape.hpp"

#include <glm/vec3.hpp>

template <typename T>
struct PhysicsBody {
    glm::tvec3<T> pos;
    glm::tvec3<T> vel;
    glm::tvec3<T> accel;
    T mass;
    T restitution;
    Shape* shape;

    void applyForce(glm::tvec3<T> force);
    void applyForceX(T force);
    void applyForceY(T force);
    void applyForceZ(T force);
    void applyImpulse(glm::tvec3<T> impulse);
    void applyImpulseX(T impulse);
    void applyImpulseY(T impulse);
    void applyImpulseZ(T impulse);
    void update(T step);

    T getInverseMass() const;
};

#include "physics_body.inl"

typedef PhysicsBody<float> PBody;