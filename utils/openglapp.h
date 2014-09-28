#ifndef OPENGLAPP_H
#define OPENGLAPP_H

class GLFWwindow;

class OpenGLApp {
public:

    OpenGLApp();
    ~OpenGLApp();

    void run();

private:

    virtual void setup();
    virtual void render(double time) = 0;
    virtual void cleanup();


private:

    GLFWwindow* window;
};



#endif