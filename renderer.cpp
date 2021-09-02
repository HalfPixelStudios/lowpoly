
#include <GL/glew.h>

#include "headers/renderer.h"
#include "headers/glutils.h"
#include "headers/shaderutils.h"

#include <iostream>

Renderer::Renderer(void)
{
}

Renderer::~Renderer(void)
{
}

void
Renderer::draw(const VertexArrayObject& vao, const IndexBuffer& ib, Shader& shader, unsigned int vertex_count) const
{
    shader.bind();
    vao.bind();
    ib.bind();

    glCall(glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, nullptr));
}

void
Renderer::drawMesh(const Mesh& mesh, Shader& shader)
{
    draw(mesh.getVAO(), mesh.getIB(), shader, mesh.getIndicesSize());
}

void
Renderer::clear(void) const
{
    glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
}

