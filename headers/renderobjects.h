
#ifndef __RENDEROBJECTS_H__
#define __RENDEROBJECTS_H__

#include "glm/glm.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "glutils.h"

class VertexBuffer;

struct Vertex {
    glm::vec3 position;
    glm::vec2 texcoord;
    glm::vec3 normal;
};

struct VertexAttrib {
    GLenum type;
    int count;
GLenum normalized;
};

class VertexArrayObject
{
private:
    unsigned int renderer_id;
    std::vector<VertexAttrib> layout;
    int stride;
public:
    VertexArrayObject(void);
    ~VertexArrayObject(void);
    template<typename T> void addAttribute(int count);
    void bindToVertexBuffer(VertexBuffer& vb);
    void bind(void);
    void unbind(void);
};

class VertexBuffer
{
private:
    unsigned int renderer_id;
public:
    VertexBuffer(float* positions, int count, GLenum usage_mode); // depricate float* sometime
    VertexBuffer(std::vector<Vertex> positions, GLenum usage_mode);
    ~VertexBuffer(void);
    void bind(void) const;
    void unbind(void) const;
};

class IndexBuffer
{
private:
    unsigned int renderer_id;
public:
    IndexBuffer(unsigned int* indicies, int count, GLenum usage_mode);
    IndexBuffer(std::vector<unsigned int> indicies, GLenum usage_mode);
    ~IndexBuffer(void);
    void bind(void) const;
    void unbind(void) const;
};

#endif // __RENDEROBJECTS_H__
