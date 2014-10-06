#include <iostream>
#include <memory>
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

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexStorage2D(GL_TEXTURE_2D,
                       1, // Mipmap level
                       GL_RGBA32F,
                       256, 256);

        std::unique_ptr<float[]> texture = createTexture();
        glTexSubImage2D(GL_TEXTURE_2D,
                        0, // level 0
                        0, 0, // offset,
                        256, 256, // size
                        GL_RGBA,
                        GL_FLOAT,
                        texture.get());

        texture.reset();
    }

    std::unique_ptr<float[]> createTexture() {
        auto texture = std::unique_ptr<float[]>(new float[256*256 * 4]);

        int x, y;
        int width = 256;
        int height = 256;

        float * data = texture.get();

        for (y = 0; y < height; y++)
        {
            for (x = 0; x < width; x++)
            {
                data[(y * width + x) * 4 + 0] = (float)((x & y) & 0xFF) / 255.0f;
                data[(y * width + x) * 4 + 1] = (float)((x | y) & 0xFF) / 255.0f;
                data[(y * width + x) * 4 + 2] = (float)((x ^ y) & 0xFF) / 255.0f;
                data[(y * width + x) * 4 + 3] = 1.0f;
            }
        }

        return texture;
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
        glDeleteTextures(1, &texture);
    }

private:
    GLuint program;
    GLuint vertex_array_object;
    GLuint texture;
};


int main(void)
{
    PixelApp app;
    app.run();
   
    return 0;
}