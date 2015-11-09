#include <glm/mat4x4.hpp>
#include <logger.h>
#include <myglutils.h>

#include "cube.hpp"

void Cube::setVPM(glm::mat4 VPM) {
    MVP = new glm::mat4(VPM);
}

void Cube::setup() {
<<<<<<< HEAD
    const char* objectPath = "Resources/cube.obj";
    float* vertices;
    int length;
    loadWavefront1(objectPath, &vertices, &length);
    
    assert(length == 36 * 3);
    
=======
    const char* objectPath = "Resources/suzanne.obj";
    float* vertices;
    loadWavefront1(objectPath, &vertices, &length);
    
>>>>>>> SPC-Week-Branch-2
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
    glUniform3f(camPosID, 0, 1, 5);
    
    glDrawArrays(GL_TRIANGLES, 0, length / 3);
}
