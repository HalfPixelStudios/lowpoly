#ifndef __SHADERUTILS_H__
#define __SHADERUTILS_H__

#include <string>
#include "glutils.h"

class Shader
{
private:
    unsigned int renderer_id;
public:
    Shader(std::string vertex_shader_path, std::string fragment_shader_path);
    ~Shader(void);
    void bind(void);
    void unbind(void);
    int getUniformLocation(std::string uniform_name);

private:
    static std::string readShader(std::string filepath);
    static unsigned int generateShader(const std::string& vertex_shader, const std::string& fragment_shader);
    static unsigned int compileShader(unsigned int type, const std::string& src);
};

#endif // __SHADERUTILS_H__
