#include <iostream>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "openglapp.h"
#include "mat.h"
#include "util.h"
#include <memory>
#include <SOIL/SOIL.h>

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

        // QUAD OBJECT
        GLfloat points[] = {
            -1.0, 1.0, 0.5,
            1.0, 1.0, 0.5, 
            1.0, -1.0, 0.5,
            -1.0, -1.0, 0.5, 
        };

        GLfloat texture_points[] = {
            0.0, 0.0,
            1.0, 0.0,
            1.0, -1.0,
            -1.0, -1.0,
        };

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        int width, height;
        unsigned char* img = SOIL_load_image("icon.png", &width, &height, NULL, SOIL_LOAD_RGBA);   

        /*width = 256;
        height = 256;
        */

        //glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, 256, 256);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);

        //auto tex_image = createTexture();
        
        //glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 256, 256, GL_RGBA, GL_FLOAT, tex_image.get());
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, img);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, tex_image.get());

        
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glGenBuffers(2, quad_buffers);
        glBindBuffer(GL_ARRAY_BUFFER, quad_buffers[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, quad_buffers[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texture_points), texture_points, GL_STATIC_DRAW);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(1);
            
        glBindVertexArray(vertex_array_object);    
         glEnable(GL_BLEND);

        //glEnable(GL_CULL_FACE); 
        //glFrontFace(GL_CW);

        //glEnable(GL_DEPTH_TEST);
        //glDepthFunc(GL_LEQUAL);
    }

    std::unique_ptr<float[]> createTexture() {
        auto texture = std::unique_ptr<float[]>(new float[256*256 * 4]);

        int x, y;
        int width = 256;
        int height = 256;

        float * data = texture.get();

        float i = 0;

        for (y = 0; y < height; y++)
        {
            for (x = 0; x < width; x++)
            {
                data[(y * width + x) * 4 + 0] = i / 255.0f;
                data[(y * width + x) * 4 + 1] = i / 255.0f;
                data[(y * width + x) * 4 + 2] = i / 255.0f;
                data[(y * width + x) * 4 + 3] = 1.0f;
                i++;  
            }
            i = 0.0;
        }

        return texture;
    }

    void render(double current_time) {
        glViewport(0,0, 640, 480);
        //static const GLfloat one = 1.0f;
        //glClearBufferfv(GL_DEPTH, 0, &one);
        GLfloat color[] = {
            0.0f,
            0.0f,
            0.0f, 
            1.0f
        };
        glClearBufferfv(GL_COLOR, 0, color);

        glUseProgram(program);

        auto proj_matrix = math::perspective(50.0, 640.0/480.0, 0.1, 1000.0);
        auto proj_matrix_loc = glGetUniformLocation(program, "proj_matrix");
        glUniformMatrix4fv(proj_matrix_loc, 1, GL_FALSE, proj_matrix.array());


        auto mv_matrix = math::translate( 0.0f, 0.0, -6.0);
        auto mv_matrix_loc = glGetUniformLocation(program, "mv_matrix");
        glUniformMatrix4fv(mv_matrix_loc, 1, GL_FALSE, mv_matrix.array());

        glDrawArrays(GL_QUADS, 0, 4);
    }

    void cleanup() {
        glDeleteVertexArrays(1, &vertex_array_object);
        glDeleteProgram(program);
        glDeleteBuffers(2, quad_buffers);
        glDeleteTextures(1, &texture);
    }

private:
    GLuint program;
    GLuint vertex_array_object;
    GLuint quad_buffers[2];
    GLuint texture;
};


int main(void)
{
    PixelApp app;
    app.run();
   
    return 0;
}
