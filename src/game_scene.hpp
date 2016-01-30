#pragma once

#include "game_node.hpp"
#include "myglutils.h"
#include "player.hpp"

class GameScene: public GameNode {
    public:
        Player player = Player(0.0, 1.5, 0.0);

        GameScene(GLFWwindow* window);

        GLFWwindow* getWindow();
        glm::vec3 getPlayerPos();
        glm::mat4 getVPM();

        bool setup() override;
        void render(float interp) override;
        void update(double step) override;

    private:
        GLFWwindow* window;
        bool isSetup = false;
};
