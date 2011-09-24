#ifndef QBZ_TERRAIN_H
#define QBZ_TERRAIN_H

#include "World/qbz_model.h"

namespace qbz {

    class Model;

    class Terrain : public Model {

    public:
        Terrain(float bl_x=0.0f, float bl_y=0.0, float tr_x=1.0, float tr_y=1.0);
        void populateFromHeightMap(const std::string & filename);
        void populateFromNoise(int seed);
        vertex * getSurroundingVertices(int index);


    private:
        qbz::vertex * vertices;
        GLushort* indices;
        int x_res, y_res, quad_count, BL, BR, TR, TL, buffer_size, element_count;
        float step;

        /* texture data */
        GLuint texHeightMap;
};


};

#endif // QBZ_TERRAIN_H
