#ifndef __SHADERUTILS_H__
#define __SHADERUTILS_H__

std::string readShader(std::string filepath);
unsigned int generateShader(const std::string& vertexShader, const std::string& fragmentShader);
unsigned int compileShader(unsigned int type, const std::string& src);

#endif // __SHADERUTILS_H__
