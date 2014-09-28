#include <fstream>

void print_info_log(GLint obj) {
    GLsizei length;
    GLchar info_log[256];
    glGetShaderInfoLog(obj, 256, &length, info_log);
    std::cout << info_log;
}

std::string load_file(std::string& filename) {
    std::ifstream f(filename.c_str());
    std::string content((std::istreambuf_iterator<GLchar>(f)), 
                        std::istreambuf_iterator<GLchar>());
    return content;
}

GLuint create_shader(std::string filename, GLenum shader_type) {
    const std::string source = load_file(filename);
    GLuint shader = glCreateShader(shader_type);
    const GLchar* ptr_to_source = source.c_str();
    glShaderSource(shader, 1, (const GLchar**)&ptr_to_source, NULL);
    glCompileShader(shader);
    print_info_log(shader);
    return shader;
}
