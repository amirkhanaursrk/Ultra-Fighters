#include "wavefront_object.hpp"
#include "game_scene.hpp"

#include <glm/mat4x4.hpp>

#include "logger.h"
#include "myglutils.h"

WavefrontObject::WavefrontObject(const char* path) {
    this->path = path;
}

bool WavefrontObject::setup() {
    float* vertices;
    assert(loadWavefront1(path, &vertices, &length));
    
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

    if (!vao || !program) {
        return false;
    }
    
    log_msg(LOG_INFO, "Finished setting up WavefrontObject\n");

    return true;
}

void WavefrontObject::render(float interp) {
    glBindVertexArray(vao);
    glUseProgram(program);
    
    GLint VPMID = glGetUniformLocation(program, "MVP");
    assert(VPMID != -1);
    glUniformMatrix4fv(VPMID, 1, GL_FALSE, &scene->getVPM()[0][0]);

    GLint camPosID = glGetUniformLocation(program, "camPos");
    assert(camPosID != -1);
    glUniform3f(camPosID, 0, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, length / 3);
}
