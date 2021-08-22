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
    VertexArrayObject vao;
    VertexBuffer vb;
    IndexBuffer ib;
    unsigned int index_size;
public:
    Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures, std::vector<unsigned int> indices);
    ~Mesh(void);
    inline const VertexArrayObject& getVAO(void) const { return vao; }
    inline const IndexBuffer& getIB(void) const { return ib; }
    inline unsigned int getIndicesSize(void) const { return index_size; }
};


#endif // __MESH_H__
