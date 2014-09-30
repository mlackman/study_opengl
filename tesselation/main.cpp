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
        GLuint tcs_shader = create_shader("tcs.shd", GL_TESS_CONTROL_SHADER);
        GLuint tes_shader = create_shader("tes.shd", GL_TESS_EVALUATION_SHADER);

        program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, tcs_shader);
        glAttachShader(program, tes_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        glDeleteShader(tcs_shader);
        glDeleteShader(tes_shader);

        glGenVertexArrays(1, &vertex_array_object);
        glBindVertexArray(vertex_array_object);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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

        // Use this code in comments to move the triange with mouse and
        // comment out the other attrib definition
        /* 
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        
        GLfloat attrib[] = {
            (float)mouseX/320.0f-1.0f,
            -(float)mouseY/240.0f+1.0f,
            0.0f,
            0.0f
        };*/
        GLfloat attrib[] = {
            (float)sin(current_time) * 0.5f,
            (float)cos(current_time) * 0.6f,
            0.0f,
            0.0f
        };
        // update the value of vertex shader input attribute 0
        glVertexAttrib4fv(0, attrib);



        glDrawArrays(GL_PATCHES, 0, 3);
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

