
#include "headers/model.h"

Model::Model(std::string model_path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(model_path, aiProcess_Triangulate | aiProcess_FlipUVs);

    /* check if imported correctly */
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "error loading model: " << importer.GetErrorString() << std::endl;
        return;
    }

    load_node(scene, scene->mRootNode);

}

Model::~Model(void)
{
    for (int i = 0; i < meshes.size(); i++)
        delete meshes[i];
}

void
Model::load_node(const aiScene* scene, aiNode* node)
{
    /* load each of this node's meshes */
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(convert_mesh(mesh));
    }

    /* load each of the node's children */
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        load_node(scene, node->mChildren[i]);
    }
}

Mesh*
Model::convert_mesh(aiMesh* mesh)
{
    /* process vertices */
    std::vector<Vertex> vertices;
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        glm::vec3 position = glm::vec3(
            mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z
        );
        glm::vec2 texcoord = (mesh->mTextureCoords[0]) ?
            glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y) :
            glm::vec2(0.0f, 0.0f);
        glm::vec3 normal = glm::vec3(
            mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z 
        );

        vertices.push_back(Vertex{ position, texcoord, normal });
    }

    /* TODO process textures */
    std::vector<Texture> textures;

    /* process indices */
    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    return new Mesh(vertices, textures, indices);
}
