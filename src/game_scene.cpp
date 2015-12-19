#include "logger.h"
#include "myglutils.h"
#include "miscutils.hpp"
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

bool GameScene::setup() {
    glfwMakeContextCurrent(window);
    
    glClearColor(0.3, 0.3, 0.8, 1.0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glfwSetCursorPos(window, 0, 0);

    isSetup = true;
    return true;
}

static void rrender(GameNode* node, float interp) {
    if (node->parent != NULL) {
        node->render(interp);
    }

    for (GameNode* child : node->children) {
        rrender(child, interp);
    }
}

void GameScene::render(float interp) {
    if (!isSetup) return;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    rrender(this, interp);

    glfwSwapBuffers(window);
}

static void rupdate(GameNode* node, double step) {
    for (GameNode* newChild : node->newChildren) {
        if (newChild->setup()) {
            node->children.push_back(newChild);
        }
        else {
            log_msg(LOG_WARNING, "Child %p failed setup. (parent=%p)\n", newChild, node);
        }
    }

    for (GameNode* oldChild : node->oldChildren) {
        delete oldChild;
    }

    node->newChildren.clear();
    node->oldChildren.clear();

    if (node->parent != NULL) {
        node->update(step);
    }

    for (GameNode* child : node->children) {
        rupdate(child, step);
    }
}

void GameScene::update(double step) {
    if (!isSetup) setup();

    rupdate(this, step);
}
