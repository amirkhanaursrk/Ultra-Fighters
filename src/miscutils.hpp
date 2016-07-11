#pragma once

#include <math.h>
#include <vector>

#include "triangle.hpp"

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795028
#endif

#define SQR(x) ((x) * (x))

template <typename T>
void ezremove(std::vector<T>& v, T val);

float* flatten(const std::vector<Triangle> tris, size_t* n);
void loadOctahedron(std::vector<Triangle> &v);
void subdivide(std::vector<Triangle> &tris);

const char* getShapeName(ShapeType s);