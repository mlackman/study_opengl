#include "openglapp.h"
#include <system_error>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

OpenGLApp::OpenGLApp() : window(0) {
    if (!glfwInit()) {
        throw std::system_error(std::error_code(-1, std::generic_category()),
                                "glfwInit failed!");
    }
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw std::system_error(std::error_code(-1, std::generic_category()),
                                "glfwCreateWindow failed!");
    } 
    glfwMakeContextCurrent(window);
    GLenum err = glewInit();
    if (err != 0) {
        glfwTerminate();
        throw std::system_error(std::error_code(-1, std::generic_category()),
                                "glewInit failed!");
    }
}

OpenGLApp::~OpenGLApp() {
    glfwTerminate();
}

void OpenGLApp::run() {
    setup();
    while (!glfwWindowShouldClose(window)) {
        render(glfwGetTime());
        
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    cleanup();
}

void OpenGLApp::setup() {}
void OpenGLApp::cleanup() {}
