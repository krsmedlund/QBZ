#include "qbz_particlebase.h"

#include "qbz_model.h"
#include "qbz_renderprogram.h"

using namespace qbz;

ParticleBase::ParticleBase(glm::vec3 & pos, glm::vec3 & dir, float speed, float size)
{
    this->position = pos;
    this->direction = dir;
    this->speed = speed;
    this->size = size;
    alive = true;
}

ParticleSystem::ParticleSystem(Model * model, RenderProgram * renderProgram) {
    this->model = model;
    this->renderProgram = renderProgram;
    nParticles = 0;
}

void ParticleSystem::addParticle(glm::vec3 & pos, glm::vec3 & dir, float speed, float size) {
    nParticles++;
    if (nParticles < MAX_PARTICLES)
        this->particles.push_back(new ParticleBase(pos, dir, speed, size));
}

void ParticleSystem::updateParticles() {
    for (int i=0; i<nParticles; i++) {
        if (!particles[i]->alive)
            continue;
        particles[i]->position -= (particles[i]->direction * particles[i]->speed);
        model->setPosition(particles[i]->position);
        model->setScale(particles[i]->size, particles[i]->size, particles[i]->size);
        model->rotate(particles[i]->size / 50.0f, 0.0f, 1.0f, 0.0f);
        this->renderProgram->drawObject(model);

        if (particles[i]->position.y < -1.0) {
            particles[i]->position.y = 5.0f + 2.0*(float)rand()/(float)RAND_MAX;
            particles[i]->position.x = -0.3f + 3.0*(float)rand()/(float)RAND_MAX;
            particles[i]->position.z = -0.3f + 3.0*(float)rand()/(float)RAND_MAX;
            particles[i]->size = 0.4f * (float)rand()/(float)RAND_MAX;
            particles[i]->speed = 0.01f + (float)rand()/(float)RAND_MAX / 7.0f;
        }
    }
}
