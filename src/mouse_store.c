#include "mouse_store.h"

static double mouseX = 0;
static double mouseY = 0;

void getMousePos(double* x, double* y) {
	*x = mouseX;
	*y = mouseY;
}

void mousePosStoreCallback(GLFWwindow* window, double xpos, double ypos) {
	mouseX = xpos;
	mouseY = ypos;
}
