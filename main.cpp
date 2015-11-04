#include <libgen.h> // dirname
#include <logger.h> // log_msg
#include <myglutils.h> // GLFW, GLEW, and setup functions
#include <unistd.h> // chdir

#include "game_scene.hpp" // GameScene
#include "key_listener.hpp" // addKeyListener, listenerKeyCallback

int main(int argc, char* argv[]) {
    if (!setupGLFW()) return 1;
    setupApple();

    chdir(dirname(argv[1]));
    set_log_file(fopen("ultra_fighters.log", "a"));
    setDebug(true);
    setBind(true);
    
    log_msg(LOG_INFO, "Started Ultra Fighters!\n");
    
    GLFWwindow* window = glfwCreateWindow(640, 480, "Ultra Fighters", NULL, NULL);
    
    if (!window) {
        log_msg(LOG_ERROR, "GLFW3 window creation failed.\n");
        
        return 1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, listenerKeyCallback);
    
    if (!setupGLEW()) return 1;
    
    GameScene* scene = new GameScene(window);
    Loop loop = Loop(scene);
    loop.start();
    
    addKeyListener(scene);
    
    log_msg(LOG_INFO, "OpenGL Vendor: %s\n", glGetString(GL_VENDOR));
    log_msg(LOG_INFO, "OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
    log_msg(LOG_INFO, "OpenGL Version: %s\n", glGetString(GL_VERSION));
    log_msg(LOG_INFO, "GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    log_msg(LOG_INFO, "GLEW Version: %s\n", glewGetString(GLEW_VERSION));
    log_msg(LOG_INFO, "GLFW Version: %d.%d.%d\n", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);
    log_msg(LOG_INFO, "Started loop!\n");
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
    
    loop.stop();
    glfwTerminate();
    
    return 0;
}
