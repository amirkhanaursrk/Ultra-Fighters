#pragma once

#include <GLFW/glfw3.h>

#include "game_node.hpp"
#include "player.hpp"

class GameScene: public GameNode {
    public:
        Player player = Player(0.0, 1.5, 0.0);

        GameScene(GLFWwindow* window);
        void setCamPos(glm::vec3 pos) override;
        void setVPM(glm::mat4 VPM) override;
        void setup() override;
        void render(float interp) override;
        void update(double step) override;

    private:
        GLFWwindow* window;
};
