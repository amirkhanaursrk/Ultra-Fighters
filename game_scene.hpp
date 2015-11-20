#pragma once

#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "parent_game_object.hpp"

class GameScene: public ParentGameObject {
    public:
        GameScene(GLFWwindow* window);
        void setup() override;
        void render(float interp) override;
        void update(double step) override;

    private:
        GLFWwindow* window;
        glm::vec3 camPos = glm::vec3(0.0, 0.5, 0.0);
        glm::vec3 camTarget = glm::vec3(1.5, 0.5, 1.5);
        
        void updateVPM();
};
