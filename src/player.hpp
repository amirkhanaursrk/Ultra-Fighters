#pragma once

#include "game_node.hpp"
#include "physics_body.hpp"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

class Player: public GameNode {
    public:
        Player(double x, double y, double z); // Player at pos
        Player(); // Player at origin

        void setCamPos(glm::vec3 pos) override {}
        void setVPM(glm::mat4 VPM) override {}
        void setup() override;
        void render(float interp) override {}
        void update(double step) override;

        glm::mat4 getVPM(); // calculate and return VPM
        bool VPMchanged(); // getter for VPMhasChanged

    private:
        PBody body = { 80 };
        const glm::vec3 up = glm::vec3(0.0, 1.0, 0.0); // The direction of up
        const glm::vec3 out = glm::vec3(1.0, 0.0, 0.0); // The default direction of out (could be anything)
        const glm::vec3 side = glm::cross(up, out); // Left or Right, doesn't matter as long as it's consistent
        float yaw; // rotation around up
        float pitch; // tilt "upwards" or "downwards"
        bool VPMhasChanged; // has the VPM changed since last fetched?
        double mouseX;
        double mouseY;
};
