#include <fstream>
#include <cstdlib>

void print_info_log(GLint obj, const std::string& filename) {
    GLsizei length;
    GLchar info_log[256];
    glGetShaderInfoLog(obj, sizeof(info_log), &length, info_log);
    std::cout << filename << ":" << info_log << std::endl;
}

std::string load_file(const std::string& filename) {
    std::ifstream f(filename.c_str());
    if (f.is_open()) {
        std::string content((std::istreambuf_iterator<GLchar>(f)), 
                             std::istreambuf_iterator<GLchar>());
        return content;
    } else {
        std::cout << filename << " could not be opened!" << std::endl;
        std::exit(-1);
    }

}

GLuint create_shader(std::string filename, GLenum shader_type) {
    const std::string source = load_file(filename);
    GLuint shader = glCreateShader(shader_type);
    const GLchar* ptr_to_source = source.c_str();
    glShaderSource(shader, 1, (const GLchar**)&ptr_to_source, NULL);
    glCompileShader(shader);
    print_info_log(shader, filename);
    return shader;
}
