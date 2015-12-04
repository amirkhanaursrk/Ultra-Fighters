#include "physics_body.hpp"

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

    x += Vx * step + Ax * step * step / (T) 2;
    y += Vy * step + Ay * step * step / (T) 2;
    z += Vz * step + Az * step * step / (T) 2;

    Ax = 0;
    Ay = 0;
    Az = 0;
}

template struct PhysicsBody<float>;
//template struct PhysicsBody<double>;
