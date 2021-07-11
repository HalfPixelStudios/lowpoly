
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

#include "headers/shaderutils.h"
#include "headers/glutils.h"

Shader::Shader(std::string vertex_shader_path, std::string fragment_shader_path)
{
    std::string vertex_shader = Shader::readShader(vertex_shader_path);
    std::string fragment_shader = Shader::readShader(fragment_shader_path);

    // TODO: check for errors reading shader files

    renderer_id = generateShader(vertex_shader, fragment_shader);
}

Shader::~Shader(void)
{
}

void
Shader::bind(void)
{
    glCall(glUseProgram(renderer_id));
}

void
Shader::unbind(void)
{
    glCall(glUseProgram(0));
}

int
Shader::getUniformLocation(std::string uniform_name)
{
    return glGetUniformLocation(renderer_id, uniform_name.c_str());
}

/* reads shader file into string */
std::string
Shader::readShader(std::string filepath)
{
    std::ifstream handle;
    std::stringstream buf;

    handle.open(filepath);
    if (handle.fail()) {
        std::cerr << "Failed to open shader file: " << std::strerror(errno) << std::endl; 
        return nullptr;
    }

    buf << handle.rdbuf();
    handle.close();

    return buf.str();
}

/* creates shader program */
unsigned int
Shader::generateShader(const std::string& vertex_shader, const std::string& fragment_shader)
{
    unsigned int prog = glCreateProgram();    
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertex_shader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragment_shader);

    glCall(glAttachShader(prog, vs));
    glCall(glAttachShader(prog, fs));
    glCall(glLinkProgram(prog));
    glCall(glValidateProgram(prog));

    glCall(glDeleteShader(vs));
    glCall(glDeleteShader(fs));

    return prog;
}

/* compiles individual shader from source string */
unsigned int
Shader::compileShader(unsigned int type, const std::string& src)
{
    unsigned int id = glCreateShader(type);
    const char* csrc = src.c_str();
    glCall(glShaderSource(id, 1, &csrc, nullptr));
    glCall(glCompileShader(id));

    /* get shader compilation result */
    int comp_result;
    glCall(glGetShaderiv(id, GL_COMPILE_STATUS, &comp_result));
    if (comp_result == GL_FALSE) {
        int err_len;
        glCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &err_len));
        char* err_msg = (char*)alloca(err_len*sizeof(char));
        glCall(glGetShaderInfoLog(id, err_len, &err_len, err_msg));

        std::cout << "Failed to compile shader" << std::endl;
        std::cout << err_msg << std::endl;
        glCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

