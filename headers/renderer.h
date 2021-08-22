
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "renderobjects.h"
#include "shaderutils.h"

#include "mesh.h"

class Renderer
{
public:
    Renderer(void);
    ~Renderer(void);
    void draw(const VertexArrayObject& vao, const IndexBuffer& ib, Shader& shader, unsigned int vertex_count) const;
    void drawMesh(const Mesh& mesh, Shader& shader);
    void clear(void) const;
};

#endif // __RENDERER_H__
