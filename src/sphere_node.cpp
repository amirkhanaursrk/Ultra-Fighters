#include "sphere_node.hpp"
#include "miscutils.hpp"
#include "set_uniform.hpp"
#include "game_scene.hpp"
#include "logger.h"

#include <glm/gtx/transform.hpp>

SphereNode::SphereNode(glm::vec3 center, float radius, unsigned char recLevel) {
    name = "Sphere Node";
    sphere.center = center;
    sphere.setRadius(radius);
    this->recLevel = recLevel;
}

SphereNode::SphereNode(glm::vec3 center, float radius): SphereNode(center, radius, 3) {}
SphereNode::SphereNode(float radius): SphereNode(glm::vec3(0, 0, 0), radius, 3) {}
SphereNode::SphereNode(): SphereNode(glm::vec3(0, 0, 0), 1, 4) {}

Sphere SphereNode::getSphere() const {
    return sphere;
}

bool SphereNode::setup() {
    std::vector<Triangle> sphereVertices;
    loadOctahedron(sphereVertices);

    for (int i = 0; i < recLevel; i++) {
        subdivide(sphereVertices);
    }

    size_t buff_size;
    float* flatVerts = flatten(sphereVertices, &buff_size);
    numVertices = buff_size / sizeof(float);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, buff_size, flatVerts, GL_STATIC_DRAW);

    free(flatVerts);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    program = getProgramFromFiles("Shaders/Vertex/sphere.vs.glsl", "Shaders/Fragment/generic.fs.glsl");

    return (program != -1);
}

void SphereNode::render(float interp) {
    glBindVertexArray(vao);
    glUseProgram(program);

    glm::mat4 trans = glm::translate(sphere.center);
    glm::mat4 MVP = scene->getVPM() * trans;

    setUniform(program, "MVP", MAT4, 1, &MVP[0][0]);
    setUniform(program, "r", sphere.getRadius());
    setUniform(program, "uColor", 1.0f, 0.5f, 0.0f);

    glEnable(GL_CULL_FACE);
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
    glDisable(GL_CULL_FACE);
}
