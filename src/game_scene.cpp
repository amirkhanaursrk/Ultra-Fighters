#include "myglutils.h"
#include "player.hpp"
#include "game_scene.hpp"

// The 'r' in front of the static functions stands for recursive

GameScene::GameScene(GLFWwindow* window) {
    this->window = window;
    this->scene = this;
    addChild(&player);
}

GLFWwindow* GameScene::getWindow() {
    return window;
}

glm::vec3 GameScene::getPlayerPos() {
    return player.getPos();
}

glm::mat4 GameScene::getVPM() {
    return player.getVPM();
}

void GameScene::setup() {
    glfwMakeContextCurrent(window);
    
    glClearColor(0.3, 0.3, 0.8, 1.0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

static void rrender(GameNode* node, float interp) {
    if (!node->isSetup()) {
        return;
    }

    if (node->parent != NULL) {
        node->render(interp);
    }

    for (GameNode* child : node->children) {
        rrender(child, interp);
    }
}

void GameScene::render(float interp) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    rrender(this, interp);

    glfwSwapBuffers(window);
}

static void rupdate(GameNode* node, double step) {
    if (!node->isSetup()) {
        node->setup();
        node->setSetup(true);
    }

    if (node->parent != NULL) {
        node->update(step);
    }

    for (GameNode* child : node->children) {
        rupdate(child, step);
    }
}

void GameScene::update(double step) {
    rupdate(this, step);
}
