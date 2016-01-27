#include "aabb_test_node.hpp"
#include "logger.h"
#include "intersect.hpp"

#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>

AABBTestNode::AABBTestNode(glm::vec3 pos) {
    name = "AABB Test Node";
    this->pos = pos;
    this->frame = AABB(pos, 2.0, 1.0, 1.5); // ---------------------+ @temp
}                                                               //  |
                                                               //   |
bool AABBTestNode::setup() {                                  //    |
    float* cube_points = getTriangulatedRect(2.0, 1.0, 1.5); // <---+

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, TRI_RECT_SIZE, cube_points, GL_STATIC_DRAW);

    free(cube_points);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    const char* vsPath = "Shaders/Vertex/generic.vs.glsl";
    const char* fsPath = "Shaders/Fragment/generic.fs.glsl";
    program = getProgramFromFiles(vsPath, fsPath);

    return program;
}

void AABBTestNode::render(float interp) {
    glBindVertexArray(vao);
    glUseProgram(program);
    glEnable(GL_CULL_FACE);

    glm::mat4 trans = glm::translate(pos);
    glm::mat4 MVP = scene->getVPM() * trans;

    GLint MVPID = glGetUniformLocation(program, "MVP");
    if (MVPID == -1) {
        log_msg(LOG_WARNING, "Getting the MVPID for the AABBTestNode shader failed.\n");

        return;
    }
    glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0][0]);

    GLint colorID = glGetUniformLocation(program, "uColor");
    if (colorID == -1) {
        log_msg(LOG_WARNING, "Getting the colorID for the AABBTestNode shader failed.\n");

        return;
    }
    glUniform3f(colorID, 0.7, 0, 1);

    glDrawArrays(GL_TRIANGLES, 0, TRI_RECT_VERTS);

    // if collide with player, draw small rect at top of screen

    AABB playerBox(this->scene->getPlayerPos(), 1, 1, 1);
    if (intersects(this->frame, playerBox)) {
        float infPts[] = { // 0.9, -0.9
            0.8, -0.7, 0.0,
            0.7, -0.9, 0.0,
            0.9, -0.9, 0.0,
        };

        GLuint infoVBO;
        glGenBuffers(1, &infoVBO);
        glBindBuffer(GL_ARRAY_BUFFER, infoVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(infPts), infPts, GL_STATIC_DRAW);

        GLuint infoVAO;
        glGenVertexArrays(1, &infoVAO);
        glBindVertexArray(infoVAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(0);

        MVP = glm::mat4(1);
        MVPID = glGetUniformLocation(program, "MVP");
        if (MVPID == -1) {
            log_msg(LOG_WARNING, "Getting the MVPID for the AABBTestNode shader failed.\n");

            return;
        }
        glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0][0]);

        colorID = glGetUniformLocation(program, "uColor");
        if (colorID == -1) {
            log_msg(LOG_WARNING, "Getting the colorID for the AABBTestNode shader failed. (2nd time)\n");

            return;
        }
        glUniform3f(colorID, 0, 0, 1);

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    glDisable(GL_CULL_FACE);
}

void AABBTestNode::update(double step) {}
