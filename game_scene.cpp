#include <logger.h>
#include <myglutils.h>
#include <vector>

#include "game_scene.hpp"

GameScene::GameScene(GLFWwindow* window) {
    this->window = window;
    objects = new std::vector<GameObject*>();
    unsetupObjects = new std::vector<GameObject*>();
}

void GameScene::setup() {
    glfwMakeContextCurrent(window);
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void GameScene::setVPM(glm::mat4 VPM) {
    for (int i = 0; i < objects->size(); i++) {
        (*objects)[i]->setVPM(VPM);
    }
    
    this->VPM = VPM;
}

void GameScene::render(float interp) {
    log_msg(LOG_INFO, "Rendering...\n");
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (int i = 0; i < objects->size(); i++) {
        (*objects)[i]->render(interp); // Seg fault
    }
    
    glfwSwapBuffers(window);
}

void GameScene::update(double step) {
    log_msg(LOG_INFO, "Updating...\n");
    
    if (unsetupObjects->size() != 0) {
        for (int i = 0; i < unsetupObjects->size(); i++) {
            GameObject* object = (*unsetupObjects)[i];
            object->setup();
            object->setVPM(VPM);
            objects->push_back(object);
        }
    
        unsetupObjects->clear();
    }
    
    for (int i = 0; i < objects->size(); i++) {
        (*objects)[i]->update(step);
    }
}

void GameScene::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        log_msg(LOG_INFO, "Pressed Key: %c\tRaw Key: %d\tScancode: %d\n", (char) key, key, scancode);
    }
}

void GameScene::add(GameObject* object) {
    if (object != NULL) {
        unsetupObjects->push_back(object);
    }
}