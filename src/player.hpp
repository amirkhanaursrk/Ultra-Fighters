#pragma once

#include "game_node.hpp"
#include "physics_body.hpp"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

// @todo: make player 1.8 meters tall and eyes at 1.7 meters
class Player: public GameNode {
    public:
        Player(double x, double y, double z); // Player at pos
        Player() : Player(0, 0, 0) {} // Player at origin

        bool setup() override;
        void render(float interp) override;
        void update(double step) override;

        glm::vec3 getPos();
        glm::mat4 getVPM(); // calculate and return VPM

    private:
        PBody body;
        const glm::vec3 up = glm::vec3(0.0, 1.0, 0.0); // The direction of up
        const glm::vec3 out = glm::vec3(1.0, 0.0, 0.0); // The default direction of out (could be anything)
        const glm::vec3 side = glm::cross(up, out); // Left or Right, doesn't matter as long as it's consistent
        float yaw; // rotation around up
        float pitch; // tilt "upwards" or "downwards"
        double mouseX;
        double mouseY;
        bool shotThisClick = false;
};
