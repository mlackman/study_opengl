#include <iostream>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow* window = 0;

    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

   
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    } 
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    GLenum err = glewInit();
    if (err != 0) {
        std::cout << "glewInit failed!:" << glewGetErrorString(err) << std::endl;
        return -1;
    }
    const GLubyte* renderer = glGetString (GL_RENDERER);
    std::cout << renderer << std::endl;
    const GLubyte* version = glGetString (GL_VERSION); // version as a string
    std::cout << version << std::endl;


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        double currentTime = glfwGetTime();
        GLfloat color[] = {
            (float)sin(currentTime) * 0.5f + 0.5,
            (float)cos(currentTime) * 0.5f + 0.5,
            0.0f, 
            1.0f
        };
        glClearBufferfv(GL_COLOR, 0, color);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}