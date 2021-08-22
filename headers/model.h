#ifndef __MODEL_H__
#define __MODEL_H__

#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
private:
public:
    Model(std::string model_path);
    ~Model(void);
};


#endif // __MODEL_H__
