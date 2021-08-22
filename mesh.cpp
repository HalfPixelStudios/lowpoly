
#include "headers/mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures, std::vector<unsigned int> indices)
    : vertices(vertices), textures(textures), indices(indices), vao(), vb(vertices, GL_STATIC_DRAW), ib(indices, GL_STATIC_DRAW)
{
    vb.bind();
    
    vao.addAttribute<float>(3); // position (x,y,z)
    vao.addAttribute<float>(2); // texture  (u,v)
    vao.addAttribute<float>(3); // normal   (x,y,z)
    vao.bindToVertexBuffer(vb);

    vao.unbind();
    vb.unbind();
    ib.unbind();
}

Mesh::~Mesh(void)
{
}
