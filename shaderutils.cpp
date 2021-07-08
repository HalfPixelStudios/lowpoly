
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "headers/shaderutils.h"

unsigned int
compileShader(unsigned int type, const std::string& src)
{
    unsigned int id = glCreateShader(type);
    const char* csrc = src.c_str();
    glShaderSource(id, 1, &csrc, nullptr);
    glCompileShader(id);

    /* get shader compilation result */
    int comp_result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &comp_result);
    if (comp_result == GL_FALSE) {
        int err_len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &err_len);
        char* err_msg = (char*)alloca(err_len*sizeof(char));
        glGetShaderInfoLog(id, err_len, &err_len, err_msg);

        std::cout << "Failed to compile shader" << std::endl;
        std::cout << err_msg << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int
generateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int prog = glCreateProgram();    
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);
    glValidateProgram(prog);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return prog;
}

