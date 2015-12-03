#include "physics_body.hpp"

#include <logger.h> // @temp

template <typename T>
glm::vec3 PhysicsBody<T>::pos() {
    return glm::vec3(x, y, z);
}

template <typename T>
void PhysicsBody<T>::applyForce(T Nx, T Ny, T Nz) {
    Ax += Nx / mass;
    Ay += Ny / mass;
    Az += Nz / mass;
}

template <typename T>
void PhysicsBody<T>::applyForceX(T Nx) {
    Ax += Nx / mass;
}

template <typename T>
void PhysicsBody<T>::applyForceY(T Ny) {
    Ay += Ny / mass;
}

template <typename T>
void PhysicsBody<T>::applyForceZ(T Nz) {
    Az += Nz / mass;
}

template <typename T>
void PhysicsBody<T>::update(T step) {
    Vx += Ax * step;
    Vy += Ay * step;
    Vz += Az * step;

    log_msg(LOG_DEBUG, "Float: %f\n", Vy * step + Ay * Ay / (T) 2 * step);

    x += Vx * step + Ax * Ax / (T) 2 * step;
    y += Vy * step + Ay * Ay / (T) 2 * step;
    z += Vz * step + Az * Az / (T) 2 * step;

    Ax = 0;
    Ay = 0;
    Az = 0;
}

template struct PhysicsBody<float>;
template struct PhysicsBody<double>;
