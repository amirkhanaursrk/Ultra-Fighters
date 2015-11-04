#include <assert.h>
#include <logger.h>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <myglutils.h>

#include "game_scene.hpp"

GameScene::GameScene(GLFWwindow* window) {
    this->window = window;
}

void GameScene::setup() {
    glfwMakeContextCurrent(window);
    glClearColor(0.5, 0.5, 0.8, 1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    const char* objectPath = "Resources/cube.obj";
    float* vertices;
    int length;
    loadWavefront1(objectPath, &vertices, &length);
    
    assert(length == 36 * 3);
    
    log_msg(LOG_INFO, "Loaded object file.\n");
    
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, length * sizeof(float), vertices, GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    
    const char* vertexShaderPath = "Shaders/Vertex/simple_cube_shader.vs.glsl";
    const char* fragmentShaderPath = "Shaders/Fragment/simple_cube_shader.fs.glsl";
    program = getProgramFromFiles(vertexShaderPath, fragmentShaderPath);
    
    assert(program);
    
    glm::mat4 projection = glm::perspective(45.0, 4.0 / 3.0, 0.1, 100.0);
    glm::mat4 view = glm::lookAt(glm::vec3(4, 3, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    MVP = new glm::mat4(projection * view);
}

void GameScene::setVPM(glm::mat4 VPM) {
    log_msg(LOG_WARNING, "GameScene::setVPM was called. Nothing happened.\n");
}

void GameScene::render(float interp) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glBindVertexArray(vao);
    glUseProgram(program);
    GLuint MVPID = glGetUniformLocation(program, "MVP");
    glUniformMatrix4fv(MVPID, 1, GL_FALSE, &(*MVP)[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    glfwSwapBuffers(window);
}

void GameScene::update(double step) {
}

void GameScene::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        log_msg(LOG_INFO, "Pressed Key: %c\tRaw Key: %d\tScancode: %d\n", (char) key, key, scancode);
    }
}