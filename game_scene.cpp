#include <logger.h>
#include <myglutils.h>
#include <vector>

#include "game_scene.hpp"

GameScene::GameScene(GLFWwindow* window) {
    this->window = window;
}

void GameScene::setup() {
    glfwMakeContextCurrent(window);
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void GameScene::render(float interp) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    ParentGameObject::render(interp);
    
    glfwSwapBuffers(window);
}

void GameScene::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        log_msg(LOG_INFO, "Pressed Key: %c\tRaw Key: %d\tScancode: %d\n", (char) key, key, scancode);
    }
}