#include "player.hpp"

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/transform.hpp>

#include <math.h>
#include <input/key_store.h>

Player::Player(double x, double y, double z) {
    pos = glm::vec3(x, y, z);
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
    double rotateSpeed = 0.05;

    if (getKeyAction(GLFW_KEY_RIGHT)) {
        yaw -= rotateSpeed;
        VPMhasChanged = true;
    }

    if (getKeyAction(GLFW_KEY_LEFT)) {
        yaw += rotateSpeed;
        VPMhasChanged = true;
    }

    if (getKeyAction(GLFW_KEY_UP)) {
        pitch -= rotateSpeed;
        VPMhasChanged = true;
    }

    if (getKeyAction(GLFW_KEY_DOWN)) {
        pitch += rotateSpeed;
        VPMhasChanged = true;
    }

    // check for WASD
    float moveSpeed = 1.0 / 15.0;
    
    if (getKeyAction(GLFW_KEY_W)) {
        glm::vec3 movement = glm::rotate(out, (float) yaw, up);
        pos += movement * moveSpeed;
        VPMhasChanged = true;
    }

    if (getKeyAction(GLFW_KEY_S)) {
        glm::vec3 movement = glm::rotate(out, (float) (yaw + M_PI), up);
        pos += movement * moveSpeed;
        VPMhasChanged = true;
    }

    if (getKeyAction(GLFW_KEY_A)) {
        glm::vec3 movement = glm::rotate(out, (float) (yaw + M_PI / 2.0), up);
        pos += movement * moveSpeed;
        VPMhasChanged = true;
    }

    if (getKeyAction(GLFW_KEY_D)) {
        glm::vec3 movement = glm::rotate(out, (float) (yaw - M_PI / 2.0), up);
        pos += movement * moveSpeed;
        VPMhasChanged = true;
    }

    // ...

    /*
    glm::vec3 facing = glm::vec3(2, 3, 4);
    glm::vec3 headsUp = glm::vec3(0, 1, 0);
    glm::vec3 moveDir = facing - glm::dot(facing, headsUp) * headsUp;

    log_msg(LOG_DEBUG, "Move dir: %s\n", glm::to_string(moveDir).c_str());
    */
}

glm::mat4 Player::getVPM() {
    glm::mat4 projection = glm::perspective(glm::radians(60.0), 4.0 / 3.0, 0.1, 100.0);
    glm::mat4 rotMat1 = glm::rotate((float) yaw, up);
    glm::mat4 rotMat2 = glm::rotate((float) pitch, side);
    glm::mat4 rotMat = rotMat1 * rotMat2;
    glm::vec3 target = pos + glm::vec3(rotMat * glm::vec4(out, 1.0));
    glm::vec3 headsUp = glm::vec3(rotMat * glm::vec4(up, 1.0));
    glm::mat4 view = glm::lookAt(pos, target, headsUp);
    glm::mat4 VPM = projection * view;
    VPMhasChanged = false;

    return VPM;
}

bool Player::VPMchanged() {
    return VPMhasChanged;
}