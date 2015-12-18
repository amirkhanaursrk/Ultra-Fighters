#include "projectile.hpp"
#include "game_scene.hpp"
#include "logger.h"

GLuint Projectile::vao = -1;
GLuint Projectile::program = -1;

Projectile::Projectile(float x, float y, float z) {
    pos.x = x;
    pos.y = y;
    pos.z = z;
}

bool Projectile::setup() {
    if (vao == -1 || program == -1) {
        const float* cube_points = getTriangulatedRect(0.1, 0.2, 0.3);

        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, TRI_RECT_SIZE, cube_points, GL_STATIC_DRAW);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(0);

        const char* vsPath = "Shaders/Vertex/proj.vs.glsl";
        const char* fsPath = "Shaders/Fragment/proj.fs.glsl";
        program = getProgramFromFiles(vsPath, fsPath);

        if (!program) {
            vao = -1;
            program = -1;

            return false;
        }
    }

    log_msg(LOG_INFO, "New projectile at (%f, %f, %f) was created!\n", pos.x, pos.y, pos.z);

    return true;
}

void Projectile::render(float interp) {
    glBindVertexArray(vao);
    glUseProgram(program);

    GLint VPMID = glGetUniformLocation(program, "MVP");
    if (VPMID == -1) {
        log_msg(LOG_WARNING, "Getting the VPMID for the projectile shader failed.\n");

        return;
    }
    glUniformMatrix4fv(VPMID, 1, GL_FALSE, &scene->getVPM()[0][0]);

    GLint posID = glGetUniformLocation(program, "pos");
    if (posID == -1) {
        log_msg(LOG_WARNING, "Getting the posID for the projectile shader failed.\n");

        return;
    }
    glUniform3f(posID, pos.x, pos.y, pos.z);

    glDrawArrays(GL_TRIANGLES, 0, TRI_RECT_VERTS);
}

void Projectile::update(double step) {}
