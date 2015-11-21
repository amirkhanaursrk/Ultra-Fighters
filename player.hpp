#pragma once

#include "game_object.hpp"

#include <glm/vec3.hpp>

class Player: public GameObject {
	public:
		Player(double x, double y, double z);

		void setVPM(glm::mat4 VPM) override;
		void render(float interp) override;
		void update(double step) override;

		glm::mat4 getVPM();
		bool VPMchanged();

	private:
		glm::vec3 pos;
		glm::vec3 faceDir;
		glm::vec3 headsUp;

		bool VPMhasChanged;
};