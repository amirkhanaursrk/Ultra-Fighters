#include "miscutils.hpp"

#include <algorithm> // std::find
#include <glm/geometric.hpp> // glm::vec3 glm::length
#include <stdlib.h>

template <typename T>
void ezremove(std::vector<T>& v, T val) {
    int pos = std::find(v.begin(), v.end(), val) - v.begin();
    if (pos >= v.size()) return;
    v[pos] = v[v.size() - 1];
    v.pop_back();
}

#include "game_node.hpp"
template void ezremove<GameNode*>(std::vector<GameNode*>& v, GameNode* val);

float* flatten(const std::vector<Triangle> tris, size_t* n) {
    const size_t tri_size = 9;
    const size_t buff_size = tris.size() * tri_size * sizeof(float);
    float* vertexData = (float*) malloc(buff_size);

    for (int i = 0; i < tris.size(); i++) {
        Triangle t = tris[i];

        vertexData[i * tri_size + 0] = t.p1.x;
        vertexData[i * tri_size + 1] = t.p1.y;
        vertexData[i * tri_size + 2] = t.p1.z;
        vertexData[i * tri_size + 3] = t.p2.x;
        vertexData[i * tri_size + 4] = t.p2.y;
        vertexData[i * tri_size + 5] = t.p2.z;
        vertexData[i * tri_size + 6] = t.p3.x;
        vertexData[i * tri_size + 7] = t.p3.y;
        vertexData[i * tri_size + 8] = t.p3.z;
    }

    *n = buff_size;
    return vertexData;
}

void loadOctahedron(std::vector<Triangle> &v) {
    glm::vec3 p0 = glm::vec3(1, 0, 0);
    glm::vec3 p1 = glm::vec3(-1, 0, 0);
    glm::vec3 p2 = glm::vec3(0, 1, 0);
    glm::vec3 p3 = glm::vec3(0, -1, 0);
    glm::vec3 p4 = glm::vec3(0, 0, 1);
    glm::vec3 p5 = glm::vec3(0, 0, -1);

    Triangle t0(p0, p4, p2);
    Triangle t1(p2, p4, p1);
    Triangle t2(p1, p4, p3);
    Triangle t3(p3, p4, p0);
    Triangle t4(p0, p2, p5);
    Triangle t5(p2, p1, p5);
    Triangle t6(p1, p3, p5);
    Triangle t7(p3, p0, p5);

    v.push_back(t0);
    v.push_back(t1);
    v.push_back(t2);
    v.push_back(t3);
    v.push_back(t4);
    v.push_back(t5);
    v.push_back(t6);
    v.push_back(t7);
}

void subdivide(std::vector<Triangle> &tris) {
    std::vector<Triangle> newTris;
    float l = glm::length(tris[0].p1);

    for (int i = 0; i < tris.size(); i++) {
        Triangle t = tris[i];
        glm::vec3 a = glm::normalize((t.p1 + t.p2) / 2.0f) * l;
        glm::vec3 b = glm::normalize((t.p2 + t.p3) / 2.0f) * l;
        glm::vec3 c = glm::normalize((t.p3 + t.p1) / 2.0f) * l;

        Triangle t1(t.p1, a, c);
        Triangle t2(a, b, c);
        Triangle t3(a, t.p2, b);
        Triangle t4(c, b, t.p3);

        newTris.push_back(t1);
        newTris.push_back(t2);
        newTris.push_back(t3);
        newTris.push_back(t4);
    }

    tris.swap(newTris);
}