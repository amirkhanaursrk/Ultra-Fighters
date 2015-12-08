#include <fstream> // ifstream, getline
#ifndef __APPLE__
#include <libgen.h> // dirname
#endif
#include <unistd.h> // chdir

#include "hud.hpp"
#include "wavefront_object.hpp" // WavefrontObject
#include "game_scene.hpp" // GameScene
#include "key_store.h" // storeKeyCallback
#include "mouse_store.h" // mousePosStoreCallback
#include "logger.h" // log_msg
#include "myglutils.h" // GLFW, GLEW, and setup functions
#include "wininfo.h" // window width and height

int main(int argc, char* argv[]) {
    if (!setupGLFW()) return 1;
    setupApple();
    glfwWindowHint(GLFW_SAMPLES, 4);

    const char* newPath;

    #ifdef __APPLE__
    newPath = "..";
    #else
    newPath = dirname(argv[0]);
    #endif

    int cwdError;
    if ((cwdError = chdir(newPath)) != 0) {
        perror(newPath);

        return 1;
    }

    set_log_file(fopen("Resources/uf.log", "a"));
    setDebug(true);
    setBind(true);
    
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Ultra Fighters", glfwGetPrimaryMonitor(), NULL);
    //GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Ultra Fighters", NULL, NULL);

    if (!window) {
        log_msg(LOG_ERROR, "GLFW3 window creation failed.\n");
        
        return 1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, storeKeyCallback);
    glfwSetCursorPosCallback(window, mousePosStoreCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!setupGLEW()) return 1;

    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

    log_msg(LOG_INFO, "#####################################\n");
    log_msg(LOG_INFO, "Started Ultra Fighters!\n");
    log_msg(LOG_INFO, "Current Working Directory: %s\n", cwd);
    log_msg(LOG_INFO, "OpenGL Vendor: %s\n", glGetString(GL_VENDOR));
    log_msg(LOG_INFO, "OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
    log_msg(LOG_INFO, "OpenGL Version: %s\n", glGetString(GL_VERSION));
    log_msg(LOG_INFO, "GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    log_msg(LOG_INFO, "GLEW Version: %s\n", glewGetString(GLEW_VERSION));
    log_msg(LOG_INFO, "GLFW Version: %d.%d.%d\n", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);
    log_msg(LOG_INFO, "Started loop!\n");
    
    GameScene scene(window);

    std::ifstream levelFile("Resources/levelname.txt");
    std::string levelName;
    std::getline(levelFile, levelName);
    WavefrontObject room(levelName.c_str());
    scene.addChild(&room);

    HUD hud;
    scene.addChild(&hud);

    Loop loop = Loop(&scene);
    loop.start();
    
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
    
    log_msg(LOG_INFO, "Stopping program...\n");
    loop.stop();
    glfwTerminate();
    
    return 0;
}