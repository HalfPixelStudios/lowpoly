
#include "headers/model.h"

Model::Model(std::string model_path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(model_path, aiProcess_Triangulate | aiProcess_FlipUVs);
}

Model::~Model(void)
{
}
