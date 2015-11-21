#pragma once

#include <GLFW/glfw3.h>

int getKeyAction(int key);
int getKeyMods(int key);

void storeKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);