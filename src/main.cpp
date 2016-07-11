#ifndef __APPLE__
#include <libgen.h> // dirname
#include <unistd.h> // chdir
#endif

#include <fstream> // ifstream, getline

#include "hud.hpp" // HUD
#include "wavefront_object.hpp" // WavefrontObject
#include "game_scene.hpp" // GameScene
#include "logger.h" // log_msg
#include "myglutils.h" // GLFW, GLEW, and setup functions

#include "sphere_node.hpp" // @temp

int main(int argc, char* argv[]) {
    if (!setupGLFW()) return 1;
    glfwWindowHint(GLFW_SAMPLES, 4);
    setupCoreGL();

    #ifndef __APPLE__
    const char* exePath = dirname(argv[0]);
    const char* resPath = "/Resources/";
    const int newPathLen = strlen(exePath) + strlen(resPath) + 1;
    char newPath[newPathLen];
    strcpy(newPath, exePath);
    strcat(newPath, resPath);

    int cwdError;
    if ((cwdError = chdir(newPath)) != 0) {
        perror(newPath);

        return 1;
    }
    #endif

    set_log_file(fopen("../Logs/uf.log", "a"));
    
    setDebug(DEBUG);
    setBind(DEBUG);
 
    #ifdef FULLSCREEN
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);
    int width = vidmode->width;
    int height = vidmode->height;
    const char* title =  "Ultra Fighters";
    GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, NULL);
    #else
    int width = 640;
    int height = 480;
    const char* title =  "Ultra Fighters";
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    #endif

    if (!window) {
        log_msg(LOG_ERROR, "GLFW3 window creation failed.\n");
        
        return 1;
    }
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

    log_msg(LOG_INFO, "#####################################\n");
    log_msg(LOG_INFO, "Started Ultra Fighters!\n");
    log_msg(LOG_INFO, "Current Working Directory: %s\n", cwd);
    log_msg(LOG_INFO, "Started loop!\n");
    
    GameScene scene(window);

    std::ifstream levelFile("levelname.txt");
    std::string levelName;
    std::getline(levelFile, levelName);
    WavefrontObject room(levelName.c_str());
    scene.addChild(&room);

    HUD hud;
    scene.addChild(&hud);

    SphereNode snode(glm::vec3(-2, 2, 4), 0.75); // @temp
    scene.addChild(&snode); // @temp

    Loop loop = Loop(&scene);
    loop.start();
    
    while (!glfwGetKey(window, GLFW_KEY_ESCAPE) && !glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
    
    log_msg(LOG_INFO, "Stopping program...\n");
    loop.stop();
    glfwTerminate();
    
    return 0;
}
