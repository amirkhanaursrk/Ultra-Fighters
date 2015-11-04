#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>

#include "game_object.hpp"
#include "key_listener.hpp"

class GameScene: public GameObject, public KeyListener {
    public:
        GameScene(GLFWwindow* window);
        void setup() override;
        void setMVP(glm::mat4* MVP) override;
        void render(float interp) override;
        void update(double step) override;
        void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override;

    private:
        glm::mat4* MVP;
        GLFWwindow* window;
        GLuint vao;
        GLuint program;
};

#endif