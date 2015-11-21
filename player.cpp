#include "player.hpp"

#include <glm/gtc/matrix_transform.hpp>

Player::Player(double x, double y, double z) {
	pos = glm::vec3(x, y, z);
	faceDir = glm::vec3(1, 0, 0);
	headsUp = glm::vec3(0, 1, 0);
	VPMhasChanged = true;
}

void Player::setVPM(glm::mat4 VPM) {}
void Player::render(float interp) {}

void Player::update(double step) {
	// do move and turn stuff
}

glm::mat4 Player::getVPM() {
	glm::mat4 projection = glm::perspective(45.0, 4.0 / 3.0, 0.1, 100.0);
	glm::mat4 view = glm::lookAt(pos, pos + faceDir, headsUp);
	glm::mat4 VPM = projection * view;
	VPMhasChanged = false;

	return VPM;
}

bool Player::VPMchanged() {
	return VPMhasChanged;
}