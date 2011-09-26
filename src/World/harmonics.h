#ifndef QBZ_HARMONICS_H
#define QBZ_HARMONICS_H

#include "World/model.h"

namespace qbz {

    class Model;

    class Harmonics : public Model {

    public:
        Harmonics();
        void update(int p1, int p2, int p3, int p4, float f1, float f2, float f3, float f4);
        glm::vec3 eval(double theta, double phi);
        glm::vec3 calcNormal(glm::vec3 p1, glm::vec3 p2,glm::vec3 p3);
        glm::vec3 calcBitangent(vertex & v1, vertex & v2, vertex & v3);

    private:
        qbz::vertex * vertices;
        GLushort* indices;
        int x_res, y_res, quad_count, BL, BR, TR, TL, buffer_size, element_count;
        float step;

        float power[4];
        int param[4];
};


};

#endif // QBZ_HARMONICS_H
