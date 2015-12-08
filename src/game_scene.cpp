#include "myglutils.h"
#include "game_scene.hpp"

// The 'r' in front on the static functions stands for recursive

GameScene::GameScene(GLFWwindow* window) {
    this->window = window;
    addChild(&player);
}

static void rsetCamPos(GameNode* node, glm::vec3 pos) {
    if (node->parent != NULL) {
        node->setCamPos(pos);
    }

    for (GameNode* child : node->children) {
        rsetCamPos(child, pos);
    }
}

void GameScene::setCamPos(glm::vec3 pos) {
    rsetCamPos(this, pos);
}

static void rsetVPM(GameNode* node, glm::mat4 VPM) {
    if (node->parent != NULL) {
        node->setVPM(VPM);
    }

    for (GameNode* child : node->children) {
        rsetVPM(child, VPM);
    }
}

void GameScene::setVPM(glm::mat4 VPM) {
    rsetVPM(this, VPM);
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
    
    if (player.VPMchanged()) {
        setVPM(player.getVPM());
    }

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
