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
<<<<<<< HEAD
}

void GameScene::setVPM(glm::mat4 VPM) {
    for (int i = 0; i < objects->size(); i++) {
        (*objects)[i]->setVPM(VPM);
    }
    
    this->VPM = VPM;
=======
>>>>>>> SPC-Week-Branch-2
}

void GameScene::render(float interp) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
<<<<<<< HEAD
    for (int i = 0; i < objects->size(); i++) {
        (*objects)[i]->render(interp);
    }
=======
    ParentGameObject::render(interp);
>>>>>>> SPC-Week-Branch-2
    
    glfwSwapBuffers(window);
}

<<<<<<< HEAD
void GameScene::update(double step) {
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

=======
>>>>>>> SPC-Week-Branch-2
void GameScene::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key < 256) {
            log_msg(LOG_INFO, "Pressed Key: %c\t\tRaw Key: %d\tScancode: %d\n", (char) key, key, scancode);
        }
        else {
            log_msg(LOG_INFO, "Pressed Key (non-ASCII). \tRaw Key: %d\tScancode: %d\n", key, scancode);
        }
    }
}

void GameScene::add(GameObject* object) {
    if (object != NULL) {
        unsetupObjects->push_back(object);
    }
}
