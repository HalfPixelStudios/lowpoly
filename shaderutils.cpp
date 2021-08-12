
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <regex>

#include "glm/gtc/type_ptr.hpp"

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
    glCall(glDeleteProgram(renderer_id));
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

void
Shader::setUniform4f(const std::string& uniform_name, float f0, float f1, float f2, float f3)
{
    glCall(glUniform4f(getUniformLocation(uniform_name), f0, f1, f2, f3));
}

void
Shader::setUniform4f(const std::string& uniform_name, glm::vec4 v0)
{
    glCall(glUniform4f(getUniformLocation(uniform_name), v0.x, v0.y, v0.z, v0.w));
}

void
Shader::setUniform3f(const std::string& uniform_name, float f0, float f1, float f2)
{
    glCall(glUniform3f(getUniformLocation(uniform_name), f0, f1, f2));
}

void
Shader::setUniform3f(const std::string& uniform_name, glm::vec3 v0)
{
    glCall(glUniform3f(getUniformLocation(uniform_name), v0.x, v0.y, v0.z));
}

void
Shader::setUniform1f(const std::string& uniform_name, float f0)
{
    glCall(glUniform1f(getUniformLocation(uniform_name), f0));
}

void
Shader::setUniform1i(const std::string& uniform_name, int i0)
{
    glCall(glUniform1i(getUniformLocation(uniform_name), i0));
}

void
Shader::setUniformMat4f(const std::string& uniform_name, glm::mat4 m0)
{
    glCall(glUniformMatrix4fv(getUniformLocation(uniform_name), 1, GL_FALSE, glm::value_ptr(m0)));
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
        return "";
    }

    buf << handle.rdbuf();
    handle.close();

    return buf.str();
}

/* resolves #include preprocessor directive */
std::string
Shader::preprocessInclude(const std::string shader_string)
{
    std::string processed_shader; 
    std::istringstream iss(shader_string);

    std::regex query("^\\s*#include\\s+([^\\s]+)");
    std::smatch matches;    

    /* scan file line by line to look for #include call */
    for (std::string line; std::getline(iss, line); ) {

        if (!std::regex_search(line, matches, query)) {
            processed_shader += (line+"\n");
            continue;
        } 

        /* read in header file - note, include path is not relative to file for now */
        std::string header_path = matches.str(1); // matches(1) is first matching group
        std::string shader_header = readShader(header_path);
        if (shader_header.empty()) {
            std::cerr << "Failed to resolve include from file: " << header_path << std::endl; 
            continue;
        }

        processed_shader += shader_header;

    }

    return processed_shader;
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
    std::string processed_src = preprocessInclude(src);
    const char* cstr = processed_src.c_str();

    glCall(glShaderSource(id, 1, &cstr , nullptr));
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

