#include "player.hpp"

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <input/key_store.h>

Player::Player(double x, double y, double z) {
	pos = glm::vec3(x, y, z);
	yaw = 0;
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
	double rotateSpeed = 0.1;

	if (getKeyAction(GLFW_KEY_RIGHT) == GLFW_PRESS) {
		yaw -= rotateSpeed;
		VPMhasChanged = true;
	}

	if (getKeyAction(GLFW_KEY_LEFT) == GLFW_PRESS) {
		yaw += rotateSpeed;
		VPMhasChanged = true;
	}


	if (getKeyAction(GLFW_KEY_UP) == GLFW_PRESS) {
		pitch -= rotateSpeed;
		VPMhasChanged = true;
	}


	if (getKeyAction(GLFW_KEY_DOWN) == GLFW_PRESS) {
		pitch += rotateSpeed;
		VPMhasChanged = true;
	}
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