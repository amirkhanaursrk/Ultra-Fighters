#include <libgen.h> // dirname
#include <logger.h> // log_msg
#include <myglutils.h> // GLFW, GLEW, and setup functions
#include <unistd.h> // chdir

#include "cube.hpp" // Cube
#include "game_scene.hpp" // GameScene
#include <input/key_store.h> // storeKeyCallback

int main(int argc, char* argv[]) {
    if (!setupGLFW()) return 1;
    setupApple();

    chdir(dirname(argv[0]));
    set_log_file(fopen("uf.log", "a"));
    setDebug(true);
    setBind(true);
    
    GLFWwindow* window = glfwCreateWindow(640, 480, "Ultra Fighters", NULL, NULL);
    
    if (!window) {
        log_msg(LOG_ERROR, "GLFW3 window creation failed.\n");
        
        return 1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, storeKeyCallback);

    if (!setupGLEW()) return 1;

    log_msg(LOG_INFO, "#####################################\n");
    log_msg(LOG_INFO, "Started Ultra Fighters!\n");
    log_msg(LOG_INFO, "OpenGL Vendor: %s\n", glGetString(GL_VENDOR));
    log_msg(LOG_INFO, "OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
    log_msg(LOG_INFO, "OpenGL Version: %s\n", glGetString(GL_VERSION));
    log_msg(LOG_INFO, "GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    log_msg(LOG_INFO, "GLEW Version: %s\n", glewGetString(GLEW_VERSION));
    log_msg(LOG_INFO, "GLFW Version: %d.%d.%d\n", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);
    log_msg(LOG_INFO, "Started loop!\n");
    
    GameScene scene(window);
    Cube cube;
    scene.addChild(&cube);
    
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
