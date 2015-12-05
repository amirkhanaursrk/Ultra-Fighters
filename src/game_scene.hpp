#pragma once

#include <GLFW/glfw3.h>

#include "parent_game_object.hpp"
#include "player.hpp"

class GameScene: public ParentGameObject {
    public:
        GameScene(GLFWwindow* window);
        void setup() override;
        void render(float interp) override;
        void update(double step) override;

    private:
        GLFWwindow* window;
        Player player = Player(0.0, 1.5, 0.0);
};
