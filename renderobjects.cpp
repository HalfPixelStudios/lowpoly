
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "headers/glutils.h"
#include "headers/renderobjects.h"

VertexArrayObject::VertexArrayObject()
{
}

VertexArrayObject::~VertexArrayObject()
{
}


/* vertex buffer */

VertexBuffer::VertexBuffer(float* positions, int count, GLenum usage_mode)
{
    glCall(glGenBuffers(1, &(renderer_id)));
    bind();
    glCall(glBufferData(GL_ARRAY_BUFFER, count*sizeof(float), positions, usage_mode));
    unbind();
}

VertexBuffer::~VertexBuffer(void)
{
    glCall(glDeleteBuffers(1, &(renderer_id)));
}

void
VertexBuffer::bind(void) const
{
    glCall(glBindBuffer(GL_ARRAY_BUFFER, renderer_id));
}

void
VertexBuffer::unbind(void) const
{
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

/* index buffer */

IndexBuffer::IndexBuffer(unsigned int* indicies, int count, GLenum usage_mode)
{
    glCall(glGenBuffers(1, &(renderer_id)));
    bind();
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), indicies, usage_mode));
    unbind();
}

IndexBuffer::~IndexBuffer(void)
{
    glCall(glDeleteBuffers(1, &(renderer_id)));
}

void
IndexBuffer::bind(void) const
{
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id));
}

void
IndexBuffer::unbind(void) const
{
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

