#include "logger.h"
#include "miscutils.hpp"
#include "game_scene.hpp"

// The 'r' in front of the static functions stands for recursive

GameScene::GameScene(GLFWwindow* window) {
    name = "GameScene";
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
    assert(setupGLEW());

    glClearColor(0.3, 0.3, 0.8, 1.0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glfwSetCursorPos(window, 0, 0);

    log_msg(LOG_INFO, "OpenGL Vendor: %s\n", glGetString(GL_VENDOR));
    log_msg(LOG_INFO, "OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
    log_msg(LOG_INFO, "OpenGL Version: %s\n", glGetString(GL_VERSION));
    log_msg(LOG_INFO, "GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    log_msg(LOG_INFO, "GLEW Version: %s\n", glewGetString(GLEW_VERSION));
    log_msg(LOG_INFO, "GLFW Version: %d.%d.%d\n", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);

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
            log_msg(LOG_WARNING, "Node %s failed setup. (parent=%s)\n", newChild->name, node->name);
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
