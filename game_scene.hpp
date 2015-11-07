#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <vector>

#include "game_object.hpp"
#include "key_listener.hpp"

class GameScene: public GameObject, public KeyListener {
    public:
        std::vector<GameObject*>* objects;
    
        GameScene(GLFWwindow* window);
        void setup() override;
        void setVPM(glm::mat4 VPM) override;
        void render(float interp) override;
        void update(double step) override;
        void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override;
        void add(GameObject* object);

    private:
        GLFWwindow* window;
        glm::mat4 VPM;
        std::vector<GameObject*>* unsetupObjects;
};

#endif
