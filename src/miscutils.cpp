#include "miscutils.hpp"

#include <algorithm> // std::find

#include <glm/vec3.hpp> // glm::vec3
#include <glm/gtc/type_ptr.hpp> // make_vec3

template <typename T>
void ezremove(std::vector<T>& v, T val) {
    int pos = std::find(v.begin(), v.end(), val) - v.begin();
    if (pos >= v.size()) return;
    v[pos] = v[v.size() - 1];
    v.pop_back();
}

/* This function (getBoundingRects) is an idea of mine, so I have no idea if its fast or not. I
want to automatically generate a heightmap from an array of vertices which is my
map. This is a helping function. What it does is takes the array of vertices and
returns an array of 'bounding squares' for each triangle. My theory is that this
will be faster than doing a full blown line-triangle intersection test. What I'll
do is compile these bounding squares before hand (Imagine looking down the y axis
at the triangle at finding the smallest rectangle that fits around that triangle).
When I try to get the max y for each pixel, i'll first test if the x and z are in
the rectangle then do a plane-line intersection if its in to find the highest y.
The format for the bounding rects is:
x1, x2, z1, z2, continue ...
Where:
 x1 is the min x
 x2 is the max x
 z1 is the min z
 x2 is the max z
*/

float* getBoundingRects(const float* verts, size_t len) {
    float* XZSquares = (float*) malloc(len / 9 * 4);

    for (int t = 0; t < len / 9; t ++) {
        float x1 = verts[t * 9];
        float x2 = verts[t * 9 + 3];
        float x3 = verts[t * 9 + 6];

        float medx = x1 < x2 ? x1 : x2;
        XZSquares[t * 4] = medx < x3 ? medx : x3;

        medx = x1 > x2 ? x1 : x2;
        XZSquares[t * 4 + 1] = medx > x3 ? medx : x3;

        float z1 = verts[t * 9 + 2];
        float z2 = verts[t * 9 + 5];
        float z3 = verts[t * 9 + 8];

        float medz = z1 < z2 ? z1 : z2;
        XZSquares[t * 4 + 2] = medz < z3 ? medz : z3;

        medz = z1 > z2 ? z1 : z2;
        XZSquares[t * 4 + 3] = medz > z3 ? medz : z3;
    }

    return XZSquares;
}

/* returns the Y value that is on the plane of the specified triangle at the x
and z coordinated given */

float getTriangleY(float* triPtr, float x, float z) {
    glm::vec3 pt1 = glm::make_vec3(triPtr);
    glm::vec3 edge1 = pt1 - glm::make_vec3(triPtr + 3);
    glm::vec3 edge2 = pt1 - glm::make_vec3(triPtr + 6);
    glm::vec3 n = edge1 * edge2; // the normal

    // we use the first point on the triangle as the anchor point
    return (-n.x * (x - pt1.x) - n.z * (z - pt1.z)) / n.y - pt1.y;
}

#include "game_node.hpp"
template void ezremove<GameNode*>(std::vector<GameNode*>& v, GameNode* val);