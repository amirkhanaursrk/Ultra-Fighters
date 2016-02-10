template <typename T>
void PhysicsBody<T>::applyForce(glm::tvec3<T> force) {
    accel += force * getInverseMass();
}

template <typename T>
void PhysicsBody<T>::applyForceX(T force) {
    accel.x += force * getInverseMass();
}

template <typename T>
void PhysicsBody<T>::applyForceY(T force) {
    accel.y += force * getInverseMass();
}

template <typename T>
void PhysicsBody<T>::applyForceZ(T force) {
    accel.z += force * getInverseMass();
}

template <typename T>
void PhysicsBody<T>::applyImpulse(glm::tvec3<T> impulse) {
    vel += impulse * getInverseMass();
}

template <typename T>
void PhysicsBody<T>::applyImpulseX(T impulse) {
    vel.x += impulse * getInverseMass();
}

template <typename T>
void PhysicsBody<T>::applyImpulseY(T impulse) {
    vel.y += impulse * getInverseMass();
}

template <typename T>
void PhysicsBody<T>::applyImpulseZ(T impulse) {
    vel.z += impulse * getInverseMass();
}

template <typename T>
void PhysicsBody<T>::update(T step) {
    vel += accel * step;
    pos += vel * step + accel * step * step / (T) 2;
    accel *= 0;
}

template <typename T>
T PhysicsBody<T>::getInverseMass() const {
    return (mass == 0) ? 0 : 1 / mass;
}
