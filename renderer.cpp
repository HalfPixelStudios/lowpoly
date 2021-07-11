
#include <GL/glew.h>

#include "headers/renderer.h"
#include "headers/glutils.h"
#include "headers/shaderutils.h"

Renderer::Renderer(void)
{
}

Renderer::~Renderer(void)
{
}

void
Renderer::draw(VertexArrayObject& vao, IndexBuffer& ib, Shader& shader) const
{
    shader.bind();
    /* set uniforms */
    int u_Color_loc = shader.getUniformLocation("u_Color");
    glCall(glUniform4f(u_Color_loc, 1.0f, 1.0f, 0.0f, 1.0f));

    vao.bind();
    ib.bind();

    glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}

void
Renderer::clear(void) const
{
    glCall(glClear(GL_COLOR_BUFFER_BIT));
}

