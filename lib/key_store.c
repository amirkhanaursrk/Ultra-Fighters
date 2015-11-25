#include <input/key_store.h>
#include <stdlib.h>
#include <logger.h>

static int* actions = NULL;
static int* mods = NULL;
static int num_keys = 0;

static void reserve(int new_num_keys) {
	int* new_actions = (int*) malloc(new_num_keys * sizeof(int));
	int* new_mods = (int*) malloc(new_num_keys * sizeof(int));

	for (int i = 0; i < num_keys; i++) {
		new_actions[i] = actions[i];
		new_mods[i] = mods[i];
	}

	for (int i = num_keys; i < new_num_keys; i++) {
		new_actions[i] = 0;
		new_mods[i] = 0;
	}

	if (num_keys != 0) {
		free(actions);
		free(mods);
	}

	actions = new_actions;
	mods = new_mods;
	num_keys = new_num_keys;
}

int getKeyAction(int key) {
	if (key >= num_keys) {
		reserve(key + 1);
		return GLFW_RELEASE;
	}

	return actions[key];
}

int getKeyMods(int key) {
	if (key >= num_keys) {
		reserve(key + 1);
		return 0;
	}

	return mods[key];
}

void storeKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods_val) {
	if (key >= num_keys) {
		reserve(key + 1);
	}

	actions[key] = action;
	mods[key] = mods_val;
}
