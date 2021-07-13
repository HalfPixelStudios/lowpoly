#ifndef __SHADERUTILS_H__
#define __SHADERUTILS_H__

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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
    void setUniform4f(const std::string& uniform_name, float f0, float f1, float f2, float f3);
    void setUniform1i(const std::string& uniform_name, int i0);
    void setUniformMat4f(const std::string& uniform_name, glm::mat4 m0);

private:
    int getUniformLocation(std::string uniform_name);
    static std::string readShader(std::string filepath);
    static unsigned int generateShader(const std::string& vertex_shader, const std::string& fragment_shader);
    static unsigned int compileShader(unsigned int type, const std::string& src);
};

#endif // __SHADERUTILS_H__
