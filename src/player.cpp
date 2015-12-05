#include "player.hpp"

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/transform.hpp>

#include <math.h>
#include "key_store.h"

Player::Player(double x, double y, double z) {
    body.x = x;
    body.y = y;
    body.z = z;
    yaw = 3.14;
    pitch = 0;
    VPMhasChanged = true;
}

Player::Player() {
    Player::Player(0, 0, 0);
}

void Player::setVPM(glm::mat4 VPM) {}
void Player::setup() {}
void Player::render(float interp) {}

void Player::update(double step) {
    // Check for arrow keys
    float rotateSpeed = 2.0;

    if (getKeyAction(GLFW_KEY_RIGHT)) {
        yaw -= rotateSpeed * (float) step;
        VPMhasChanged = true;
    }

    if (getKeyAction(GLFW_KEY_LEFT)) {
        yaw += rotateSpeed * (float) step;
        VPMhasChanged = true;
    }

    if (getKeyAction(GLFW_KEY_UP)) {
        pitch -= rotateSpeed * (float) step;
        VPMhasChanged = true;
    }

    if (getKeyAction(GLFW_KEY_DOWN)) {
        pitch += rotateSpeed * (float) step;
        VPMhasChanged = true;
    }

    if (getKeyAction(GLFW_KEY_SPACE) && body.y <= 1.5) {
        body.applyForceY(10000);
    }

    body.applyForceY(-9.8 * body.mass);
    body.update(step);
    VPMhasChanged = true;

    if (body.y < 1.5) {
        body.y = 1.5;
        body.Vy = 0.0;
    }

    // check for WASD
    float moveSpeed = 5.0;
    
    if (getKeyAction(GLFW_KEY_W)) {
        glm::vec3 movement = glm::rotate(out, yaw, up);
        body.x += movement.x * moveSpeed * (float) step;
        body.y += movement.y * moveSpeed * (float) step;
        body.z += movement.z * moveSpeed * (float) step;
        VPMhasChanged = true;
    }

    if (getKeyAction(GLFW_KEY_S)) {
        glm::vec3 movement = glm::rotate(out, yaw + (float) M_PI, up);
        body.x += movement.x * moveSpeed * (float) step;
        body.y += movement.y * moveSpeed * (float) step;
        body.z += movement.z * moveSpeed * (float) step;
        VPMhasChanged = true;
    }

    if (getKeyAction(GLFW_KEY_A)) {
        glm::vec3 movement = glm::rotate(out, yaw + (float) M_PI / 2.0f, up);
        body.x += movement.x * moveSpeed * (float) step;
        body.y += movement.y * moveSpeed * (float) step;
        body.z += movement.z * moveSpeed * (float) step;
        VPMhasChanged = true;
    }

    if (getKeyAction(GLFW_KEY_D)) {
        glm::vec3 movement = glm::rotate(out, yaw - (float) M_PI / 2.0f, up);
        body.x += movement.x * moveSpeed * (float) step;
        body.y += movement.y * moveSpeed * (float) step;
        body.z += movement.z * moveSpeed * (float) step;
        VPMhasChanged = true;
    }
}

glm::mat4 Player::getVPM() {
    glm::mat4 projection = glm::perspective(glm::radians(60.0), 4.0 / 3.0, 0.1, 100.0);
    glm::mat4 rotMat1 = glm::rotate(yaw, up);
    glm::mat4 rotMat2 = glm::rotate(pitch, side);
    glm::mat4 rotMat = rotMat1 * rotMat2;
    glm::vec3 target = body.pos() + glm::vec3(rotMat * glm::vec4(out, 1.0));
    glm::vec3 headsUp = glm::vec3(rotMat * glm::vec4(up, 1.0));
    glm::mat4 view = glm::lookAt(body.pos(), target, headsUp);
    glm::mat4 VPM = projection * view;
    VPMhasChanged = false;

    return VPM;
}

bool Player::VPMchanged() {
    return VPMhasChanged;
}
