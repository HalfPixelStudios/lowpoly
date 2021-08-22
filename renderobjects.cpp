
#include "headers/renderobjects.h"

VertexArrayObject::VertexArrayObject(void)
    : stride(0)
{
    glCall(glGenVertexArrays(1, &renderer_id));
}

VertexArrayObject::~VertexArrayObject(void)
{
    glCall(glDeleteVertexArrays(1, &renderer_id));
}

template<> void
VertexArrayObject::addAttribute<unsigned int>(int count)
{
    layout.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    stride += count * sizeof(GLuint);
}

template<> void
VertexArrayObject::addAttribute<float>(int count)
{
    layout.push_back({ GL_FLOAT, count, GL_FALSE });
    stride += count * sizeof(GLfloat);
}

void
VertexArrayObject::bindToVertexBuffer(VertexBuffer& vb)
{
    this->bind();
    vb.bind();

    unsigned int offset = 0;
    for (unsigned int i = 0; i < layout.size(); i++) {

        glCall(glEnableVertexAttribArray(i));
        glCall(glVertexAttribPointer(
            i, layout[i].count, layout[i].type, layout[i].normalized,
            stride, (const void*)offset
        ));

        offset += layout[i].count * glSizeOfType(layout[i].type);
    }
            
}

void
VertexArrayObject::bind(void) const
{
    glCall(glBindVertexArray(renderer_id));
}

void
VertexArrayObject::unbind(void) const
{
    glCall(glBindVertexArray(0));
}

/* vertex buffer */

VertexBuffer::VertexBuffer(float* positions, int count, GLenum usage_mode)
{
    glCall(glGenBuffers(1, &(renderer_id)));
    bind();
    glCall(glBufferData(GL_ARRAY_BUFFER, count*sizeof(float), positions, usage_mode));
    unbind();
}

VertexBuffer::VertexBuffer(std::vector<Vertex> positions, GLenum usage_mode)
{
    glCall(glGenBuffers(1, &(renderer_id)));
    bind();
    glCall(glBufferData(GL_ARRAY_BUFFER, positions.size()*sizeof(Vertex), &positions[0], usage_mode));
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

IndexBuffer::IndexBuffer(std::vector<unsigned int> indicies, GLenum usage_mode)
{
    glCall(glGenBuffers(1, &(renderer_id)));
    bind();
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size()*sizeof(unsigned int), &indicies[0], usage_mode));
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

