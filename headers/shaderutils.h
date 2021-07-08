#ifndef __SHADERUTILS_H__
#define __SHADERUTILS_H__

unsigned int compileShader(unsigned int type, const std::string& src);
unsigned int generateShader(const std::string& vertexShader, const std::string& fragmentShader);

#endif // __SHADERUTILS_H__
