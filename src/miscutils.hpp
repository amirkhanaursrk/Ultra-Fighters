#pragma once

#include <math.h>
#include <vector>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795028
#endif

#define SQR(x) ((x) * (x))

template <typename T>
void ezremove(std::vector<T>& v, T val);