#define GLM_FORCE_RADIANS
#include <glm/gtx/rotate_vector.hpp>
#include <logger.h>
#include <myglutils.h>

#include "game_scene.hpp"
#include "key_store.hpp"

GameScene::GameScene(GLFWwindow* window) {
    this->window = window;
}

void GameScene::setup() {
    glfwMakeContextCurrent(window);
    glClearColor(0.3, 0.3, 0.8, 1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    updateVPM();
}

void GameScene::render(float interp) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    ParentGameObject::render(interp);
    
    glfwSwapBuffers(window);
}

void GameScene::update(double step) {
    float turnAmount = 0.0;
    
    if (getKeyAction(GLFW_KEY_RIGHT)) {
        turnAmount -= 0.5;
    }
    
    if (getKeyAction(GLFW_KEY_LEFT)) {
        turnAmount += 0.5;
    }
    
    if (turnAmount != 0) {
        camTarget = glm::rotateY(camTarget, turnAmount * (float) step);
        
        updateVPM();
    }
    
    ParentGameObject::update(step);
}

void GameScene::updateVPM() {
    glm::mat4 projection = glm::perspective(glm::radians(60.0), 4.0 / 3.0, 0.1, 100.0);
    glm::mat4 view = glm::lookAt(camPos, camTarget, glm::vec3(0, 1, 0));
    setVPM(projection * view);
}