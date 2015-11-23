#include <myglutils.h>

#include "game_scene.hpp"

GameScene::GameScene(GLFWwindow* window) {
    this->window = window;
    addChild(&player);
}

void GameScene::setup() {
    glfwMakeContextCurrent(window);
    glClearColor(0.3, 0.3, 0.8, 1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void GameScene::render(float interp) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    bool vpm_changed = player.VPMchanged();
    if (vpm_changed) {
        setVPM(player.getVPM());
    }

    ParentGameObject::render(interp);
    
    glfwSwapBuffers(window);
}

void GameScene::update(double step) {    
    ParentGameObject::update(step);
}