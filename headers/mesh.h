#ifndef __MESH_H__
#define __MESH_H__

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <string>

#include "texture.h"
#include "renderobjects.h"

class Mesh
{
private:
    std::vector<Vertex> vertices;
    std::vector<Texture> textures;
    std::vector<unsigned int> indices;
    VertexArrayObject vao;
    VertexBuffer vb;
    IndexBuffer ib;
public:
    Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures, std::vector<unsigned int> indices);
    ~Mesh(void);
    inline VertexArrayObject& getVAO(void) { return vao; }
    inline IndexBuffer& getIB(void) { return ib; }
    inline unsigned int getIndicesSize(void) const { return indices.size(); }
};


#endif // __MESH_H__
