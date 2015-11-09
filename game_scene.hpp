#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <vector>

#include "parent_game_object.hpp"
#include "key_listener.hpp"

class GameScene: public ParentGameObject, public KeyListener {
    public:
        std::vector<GameObject*>* objects;
    
        GameScene(GLFWwindow* window);
        void setup() override;
        void render(float interp) override;
        void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override;

    private:
        GLFWwindow* window;
};

#endif
