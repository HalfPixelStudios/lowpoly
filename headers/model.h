#ifndef __MODEL_H__
#define __MODEL_H__

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>
#include <iostream>

#include "mesh.h"

class Model
{
private:
    std::vector<Mesh> meshes;
public:
    Model(std::string model_path);
    ~Model(void);
private:
    void load_node(const aiScene* scene, aiNode* node);
    Mesh convert_mesh(aiMesh* mesh);
};


#endif // __MODEL_H__
