#pragma once

#include <GLFW/glfw3.h>

#ifdef __cplusplus
extern "C" {
#endif

void getMousePos(double* x, double* y);
void mousePosStoreCallback(GLFWwindow* window, double xpos, double ypos);

#ifdef __cplusplus
}
#endif
