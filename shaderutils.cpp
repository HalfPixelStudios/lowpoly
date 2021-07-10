
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

#include "headers/shaderutils.h"
#include "headers/glutils.h"

/* reads shader file into string */
std::string
readShader(std::string filepath)
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
generateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int prog = glCreateProgram();    
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

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
compileShader(unsigned int type, const std::string& src)
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

