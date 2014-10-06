#include <iostream>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "openglapp.h"
#include "util.h"
#include "mat.h"

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

        static const GLfloat vertex_positions[] =
        {
            -0.25f,  0.25f, -0.25f,
            -0.25f, -0.25f, -0.25f,
             0.25f, -0.25f, -0.25f,

             0.25f, -0.25f, -0.25f,
             0.25f,  0.25f, -0.25f,
            -0.25f,  0.25f, -0.25f,

             0.25f, -0.25f, -0.25f,
             0.25f, -0.25f,  0.25f,
             0.25f,  0.25f, -0.25f,

             0.25f, -0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,
             0.25f,  0.25f, -0.25f,

             0.25f, -0.25f,  0.25f,
            -0.25f, -0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
            -0.25f,  0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
            -0.25f, -0.25f, -0.25f,
            -0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f, -0.25f,
            -0.25f,  0.25f, -0.25f,
            -0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
             0.25f, -0.25f,  0.25f,
             0.25f, -0.25f, -0.25f,

             0.25f, -0.25f, -0.25f,
            -0.25f, -0.25f, -0.25f,
            -0.25f, -0.25f,  0.25f,

            -0.25f,  0.25f, -0.25f,
             0.25f,  0.25f, -0.25f,
             0.25f,  0.25f,  0.25f,

             0.25f,  0.25f,  0.25f,
            -0.25f,  0.25f,  0.25f,
            -0.25f,  0.25f, -0.25f
        };
        GLuint buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions),
            vertex_positions, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(0);

        proj_matrix = math::perspective(50.0, 640.0/480.0, 0.1, 1000.0);

        mv_matrix_loc = glGetUniformLocation(program, "mv_matrix");
        proj_matrix_loc = glGetUniformLocation(program, "proj_matrix");

        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CW);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

    }

    void render(double current_time) {
        glViewport(0, 0, 640, 480);
        GLfloat color[] = {
            (float)sin(current_time) * 0.5f + 0.5f,
            (float)cos(current_time) * 0.5f + 0.5f,
            0.0f, 
            1.0f
        };
        glClearBufferfv(GL_COLOR, 0, color);
        static const GLfloat one = 1.0f;
        glClearBufferfv(GL_DEPTH, 0, &one);

        float f = current_time * M_PI * 0.1f;
        math::Mat4 mv_matrix = 
            math::translate( 0.0f, 0.0, -6.0) *
            math::translate(sinf(2.1 * f) * 0.5,
                            cosf(1.7 * f) * 0.5,
                            sinf(1.3 * f) * cosf(1.5 * f) * 2.0) * 
            math::rotate(0.0, current_time * 45.0, 0.0) * 
            math::rotate(current_time * 81.0, 0.0, 0.0);

        glUseProgram(program);


        glUniformMatrix4fv(mv_matrix_loc, 1, GL_FALSE, mv_matrix.array());
        glUniformMatrix4fv(proj_matrix_loc, 1, GL_FALSE, proj_matrix.array());

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void cleanup() {
        glDeleteVertexArrays(1, &vertex_array_object);
        glDeleteProgram(program);
    }

private:
    GLuint program;
    GLuint vertex_array_object;
    math::Mat4 proj_matrix;
    GLint mv_matrix_loc;
    GLint proj_matrix_loc;

};


int main(void)
{
    PixelApp app;
    app.run();
   
    return 0;
}

