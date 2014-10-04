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

        generate_data_to_buffer();

        
        
    }

    void generate_data_to_buffer() {
        static const GLfloat data[] = {
             0.25, -0.25, 0.5, 1.0,
            -0.25, -0.25, 0.5, 1.0,
             0.25,  0.25, 0.5, 1.0,
        };

        static const GLfloat colors[] = {
            0.5, 0.1, 0.5, 1.0, 
            0.7, 0.2, 0.0, 1.0,
            0.1, 1.0, 0.9, 1.0
        };

        GLuint buffers[2];
        // Generate name for two buffers
        glGenBuffers(2, buffers);
        // Bind it to the context using GL_ARRAY_BUFFER binding point
        glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

        // Tell the opengl where the data is and turn automatic vertex fetching on for
        // specified attribute
        glVertexAttribPointer(0,        // Attribute 0
                              4,        // 4 components,
                              GL_FLOAT, // Float data
                              GL_FALSE, // Not normalized
                              0,        // Tightly packed
                              NULL);    // offset 0
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), data, GL_STATIC_DRAW);
        
        glVertexAttribPointer(glGetAttribLocation(program, "color"),        // Attribute from opengl
                              4,        // 4 components,
                              GL_FLOAT, // Float data
                              GL_FALSE, // Not normalized
                              0,        // Tightly packed
                              NULL);    // offset 0
        glEnableVertexAttribArray(1);
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