#ifndef QBZ_PARTICLEBASE_H
#define QBZ_PARTICLEBASE_H

#include "qbz.h"

#define MAX_PARTICLES 1024

namespace qbz
{
    class Model;
    class RenderProgram;

    class ParticleBase
    {
    public:
        ParticleBase(glm::vec3 & pos, glm::vec3 & dir, float speed, float size);
        glm::vec3 direction;
        glm::vec3 position;
        glm::vec3 rotation;
        float speed;
        float size;
        int ttlMsec;
        bool alive;
    };


    class ParticleSystem
    {
    public:
        int time;
        RenderProgram * renderProgram;
        ParticleSystem(Model * model, RenderProgram * renderProgram);
        std::vector<ParticleBase*> particles;
        void addParticle(glm::vec3 & pos, glm::vec3 & dir, float speed, float size);
        void updateParticles();
        Model * model;
        int nParticles;
    };
};

#endif // QBZ_PARTICLEBASE_H
