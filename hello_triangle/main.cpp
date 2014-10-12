#include <iostream>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "openglapp.h"
#include "util.h"
class PixelApp : public OpenGLApp {
private:

    void setup() {
        GLuint vertex_shader = create_shader("vertex.shd", GL_VERTEX_SHADER);
        GLuint fragment_shader = create_shader("fragment.shd", GL_FRAGMENT_SHADER);

        program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        glGenVertexArrays(1, &vertex_array_object);
        glBindVertexArray(vertex_array_object);
    }

    void render(double current_time) {
        GLfloat color[] = {
            (float)sin(current_time) * 0.5f + 0.5f,
            (float)cos(current_time) * 0.5f + 0.5f,
            0.0f, 
            1.0f
        };
        glClearBufferfv(GL_COLOR, 0, color);

        glUseProgram(program);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void cleanup() {
        glDeleteVertexArrays(1, &vertex_array_object);
        glDeleteProgram(program);
    }

private:
    GLuint program;
    GLuint vertex_array_object;
};


int main(void)
{
    PixelApp app;
    app.run();
   
    return 0;
}