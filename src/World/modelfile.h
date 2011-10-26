#ifndef MODELFILE_H
#define MODELFILE_H

#include <assimp.h>
#include <aiPostProcess.h>
#include <aiScene.h>

#include "World/model.h"


namespace qbz {
namespace model {

class ModelFile : public qbz::Model
{
    NETWORK_NODE(ModelFile);

public:
    ModelFile(const std::string & nodeName);
    void loadMesh(const std::string & filename);
    void loadMaterial(const struct aiMaterial *mtl);

    vertex *vertices;
    GLushort *indices;
};
}
}

#endif // MODELFILE_H
