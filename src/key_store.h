#pragma once

#include <GLFW/glfw3.h>

#ifdef __cplusplus
extern "C" {
#endif

int getKeyAction(int key);
int getKeyMods(int key);

void storeKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

#ifdef __cplusplus
}
#endif
