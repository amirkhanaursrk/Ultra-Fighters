#include <glm/mat4x4.hpp>
#include <logger.h>
#include <myglutils.h>

#include "cube.hpp"

void Cube::setVPM(glm::mat4 VPM) {
    MVP = new glm::mat4(VPM);
}

void Cube::setup() {
    const char* objectPath = "Resources/Room.obj";
    float* vertices;
    loadWavefront1(objectPath, &vertices, &length);

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

    assert(program && vao);
    
    log_msg(LOG_INFO, "Finished setting up GameObject\n");
}

void Cube::update(double step) {
}

void Cube::render(float interp) {
    glBindVertexArray(vao);
    glUseProgram(program);
    
    GLuint MVPID = glGetUniformLocation(program, "MVP");
    assert(MVPID != -1);
    glUniformMatrix4fv(MVPID, 1, GL_FALSE, &(*MVP)[0][0]);

    GLuint camPosID = glGetUniformLocation(program, "camPos");
    assert(camPosID != -1);
    glUniform3f(camPosID, 0, 0.5, 0);
    
    glDrawArrays(GL_TRIANGLES, 0, length / 3);
}
