#ifndef _QBZ_SKYBOX_H
#define _QBZ_SKYBOX_H

#include "World/model.h"

namespace qbz
{
    class SkyboxCube : public Model
    {

    public:
        SkyboxCube();

    private:
        vertex vertices[8];
        GLushort indices[24];
        GLint buffer_size;
    };
};

#endif
