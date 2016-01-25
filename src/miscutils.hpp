#pragma once

#include <math.h>
#include <vector>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795028
#endif

template <typename T>
void ezremove(std::vector<T>& v, T val);

float* getBoundingRects(float* verts, size_t len);

float getTriangleY(const float* triPtr, float x, float z);