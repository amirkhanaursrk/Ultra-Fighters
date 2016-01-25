#include "hud.hpp"
#include "logger.h"
#include "game_scene.hpp"

HUD::HUD() {
    name = "HUD";
}

bool HUD::setup() {
    int width, height;
    glfwGetWindowSize(scene->getWindow(), &width, &height);

    float ar = (float) width / height;

    const GLfloat rad = 0.04;
    const GLfloat pointData[] = {
        -rad / ar, 0.0f,
         rad / ar, 0.0f,
            0.0f,  -rad,
            0.0f,   rad
    };

    vertices = sizeof(pointData) / sizeof(GLfloat) / 2;

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pointData), pointData, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    const char* vsPath = "Shaders/Vertex/hud.vs.glsl";
    const char* fsPath = "Shaders/Fragment/hud.fs.glsl";
    program = getProgramFromFiles(vsPath, fsPath);

    if (!vao || !program) {
        return false;
    }

    log_msg(LOG_INFO, "Finished setting up HUD\n");

    return true;
}

void HUD::render(float interp) {
    glEnable(GL_LINE_SMOOTH);
    glBindVertexArray(vao);
    glUseProgram(program);
    glDrawArrays(GL_LINES, 0, vertices);
}

void HUD::update(double step) {}
