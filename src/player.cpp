#include "projectile.hpp"
#include "player.hpp"

#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/gtx/rotate_vector.hpp>

#include <math.h>

#ifdef __WIN32__
#include "miscutils.hpp"
#endif

Player::Player(double x, double y, double z) {
    name = "Player";
    body = new GNPbody(this);
    body->pos.x = x;
    body->pos.y = y;
    body->pos.z = z;
    body->mass = 80;
    yaw = 3.14;
    pitch = 0.0;
}

bool Player::setup() {
    glfwGetCursorPos(scene->getWindow(), &mouseX, &mouseY);

    return true;
}

void Player::render(float interp) {}

void Player::update(double step) {
    // Check for arrow keys
    float rotateSpeed = 0.05;

    double newMouseX;
    double newMouseY;
    glfwGetCursorPos(scene->getWindow(), &newMouseX, &newMouseY);

    double xMouseDiff = newMouseX - mouseX;
    double yMouseDiff = newMouseY - mouseY;

    if (xMouseDiff != 0 || yMouseDiff != 0) {
        yaw -= rotateSpeed * step * xMouseDiff;
        pitch += rotateSpeed * step * yMouseDiff;
    }

    mouseX = newMouseX;
    mouseY = newMouseY;

    // keep the player from turning upside down
    if (pitch > M_PI / 2) {
        pitch = M_PI / 2;
    }

    if (pitch < -M_PI / 2) {
        pitch = -M_PI / 2;
    }
    // %%%%%%%%%%

    // jump
    if (glfwGetKey(scene->getWindow(), GLFW_KEY_SPACE) && body->pos.y <= 1.5) {
        body->applyImpulseY(350);
    }
    // %%%%%%%%%%

    // gravity
    body->applyForceY(-9.8 * body->mass);
    // %%%%%%%%%%

    body->update(step);

    // keep the player from falling through the floor
    if (body->pos.y < 1.5) {
        body->pos.y = 1.5;
        body->vel.y = 0.0;
    }
    // %%%%%%%%%%

    // check for WASD
    float moveSpeed = 5.0;
    
    if (glfwGetKey(scene->getWindow(), GLFW_KEY_W)) {
        glm::vec3 movement = glm::rotate(out, yaw, up);
        body->pos += movement * moveSpeed * (float) step;
    }

    if (glfwGetKey(scene->getWindow(), GLFW_KEY_S)) {
        glm::vec3 movement = glm::rotate(out, yaw + (float) M_PI, up);
        body->pos += movement * moveSpeed * (float) step;
    }

    if (glfwGetKey(scene->getWindow(), GLFW_KEY_A)) {
        glm::vec3 movement = glm::rotate(out, yaw + (float) M_PI / 2.0f, up);
        body->pos += movement * moveSpeed * (float) step;
    }

    if (glfwGetKey(scene->getWindow(), GLFW_KEY_D)) {
        glm::vec3 movement = glm::rotate(out, yaw - (float) M_PI / 2.0f, up);
        body->pos += movement * moveSpeed * (float) step;
    }

    if (glfwGetMouseButton(scene->getWindow(), GLFW_MOUSE_BUTTON_LEFT) && !shotThisClick) {
        glm::vec3 facingDir = glm::rotate(out, yaw, up);
        facingDir = glm::rotate(facingDir, pitch, glm::rotate(side, yaw, up));
        glm::vec3 projVel = glm::normalize(facingDir) * 20.0f;
        
        GNPbody projBody;
        projBody.mass = 1;
        projBody.pos = body->pos;
        projBody.vel = projVel;

        addChild(new Projectile(projBody));

        shotThisClick = true;
    }
    else if (!glfwGetMouseButton(scene->getWindow(), GLFW_MOUSE_BUTTON_LEFT)) {
        shotThisClick = false;
    }
}

glm::vec3 Player::getPos() {
    return body->pos;
}

glm::mat4 Player::getVPM() {
    int width, height;
    glfwGetWindowSize(scene->getWindow(), &width, &height);
    double aspectRatio = (double) width / height;

    glm::mat4 projection = glm::perspective(glm::radians(60.0), aspectRatio, 0.1, 100.0);
    glm::mat4 rotMat1 = glm::rotate(yaw, up);
    glm::mat4 rotMat2 = glm::rotate(pitch, side);
    glm::mat4 rotMat = rotMat1 * rotMat2;
    glm::vec3 target = body->pos + glm::vec3(rotMat * glm::vec4(out, 1.0));
    glm::vec3 headsUp = glm::vec3(rotMat * glm::vec4(up, 1.0));
    glm::mat4 view = glm::lookAt(body->pos, target, headsUp);
    glm::mat4 VPM = projection * view;

    return VPM;
}
