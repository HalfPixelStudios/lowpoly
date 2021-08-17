
#include "headers/mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures, std::vector<unsigned int> indices)
    : vertices(vertices), textures(textures), indices(indices)
{
    /* setup vao */
    /* this->vb = VertexBuffer(vertices, GL_STATIC_DRAW); */
}

Mesh::~Mesh(void)
{
}
