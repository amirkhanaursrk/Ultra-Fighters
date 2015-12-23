#include "projectile.hpp"
#include "game_scene.hpp"
#include "logger.h"

#define GLM_FORCE_RADIANS
#include <glm/gtx/vector_angle.hpp>

GLuint Projectile::vao;
GLuint Projectile::program = 0;

Projectile::Projectile(PBody body) {
    this->body = body;
}

bool Projectile::setup() {
    if (!program) {
        const float* cube_points = getTriangulatedRect(1.0, 0.1, 0.1);

        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, TRI_RECT_SIZE, cube_points, GL_STATIC_DRAW);

        free((void*) cube_points);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(0);

        const char* vsPath = "Shaders/Vertex/proj.vs.glsl";
        const char* fsPath = "Shaders/Fragment/proj.fs.glsl";
        program = getProgramFromFiles(vsPath, fsPath);

        log_msg(LOG_INFO, "Projectile did static setup succesfully: %d\n", !!program);
        return program;
    }

    return true;
}

void Projectile::render(float interp) {
    glBindVertexArray(vao);
    glUseProgram(program);

    glm::vec3 v = glm::vec3(0, -body.Vz, body.Vy);
    float a = acos(body.Vx / glm::length(body.vel()));
    glm::mat4 rotmat = glm::rotate(a, v);

    glm::mat4 trans = glm::translate(body.pos());
    glm::mat4 MVP = scene->getVPM() * trans * rotmat;

    GLint MVPID = glGetUniformLocation(program, "MVP");
    if (MVPID == -1) {
        log_msg(LOG_WARNING, "Getting the MVPID for the projectile shader failed.\n");

        return;
    }
    glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, TRI_RECT_VERTS);
}

void Projectile::update(double step) {
    body.update(step);

    timeAlive += step;
    if (timeAlive >= 20) {
        parent->removeChild(this);
    }
}