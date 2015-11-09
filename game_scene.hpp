#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "parent_game_object.hpp"
#include "key_listener.hpp"

class GameScene: public ParentGameObject, public KeyListener {
    public:
        GameScene(GLFWwindow* window);
        void setup() override;
        void render(float interp) override;
        void update(double step) override;
        void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override;

    private:
        GLFWwindow* window;
        glm::vec3 camPos = glm::vec3(0.0, 0.5, 0.0);
        glm::vec3 camTarget = glm::vec3(1.5, 0.5, 1.5);
        float turnAmount = 0.0;
        
        void updateVPM();
};

#endif
