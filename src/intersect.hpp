#pragma once

#include "aabb.hpp"
#include "sphere.hpp"

inline bool intersects(const AABB &rectA, const AABB &rectb);
inline bool intersects(const AABB &rect, const Sphere &sphere);