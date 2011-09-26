
#include <iostream>
#include <cstdlib>

#include "composer.h"

#include "System/mainwindow.h"
#include "System/library.h"

#include "GL/renderprogram.h"
#include "GL/deferredrenderer.h"
#include "GL/fbo.h"
#include "GL/rendertarget.h"

#include "World/camera.h"
#include "World/animator.h"
#include "World/world.h"
#include "World/projection_simple.h"
#include "World/projectionarea.h"
#include "World/harmonics.h"
#include "GL/skybox.h"
#include "GL/terrain.h"

using namespace qbz;

extern MainWindow* mainwindow;
extern QTime* global_time;

DeferredRenderBuffer *deferredRenderer;
Model *model, *model2, *sphere;
World *world;

qbz::SkyboxCube *sky;
qbz::FBO *ssao_fbo, *shadowMapFbo;
//qbz::FBO * shadowFbo;

float lightBumpAnim = 0.0;

qbz::Terrain * terrain;
qbz::Projection_Simple * prj;
qbz::Harmonics * harm;

GLuint t;

float lr;

network::InPort *lightRadiusPort, *lightHeightPort, *lightSpeedPort;

RenderProgram * rp;
render::RenderTarget * rt;
float fDef = 1.0f;

void Composer::setup()
{
    world = new qbz::World();
    prj = new qbz::Projection_Simple();
    Library & store = Library::open();

    // add model
    sky = new SkyboxCube();
    sky->scale(500.0, 500.0, 500.0);
    sky->material->setTexture(0, store.getTexture("skybox1.png")->handle());
/*
    network::NetworkNode* tmp = network::Factory::createNode("RenderTarget", "testName");
    delete tmp;

    rp = new RenderProgram("deferred0");
    rt = new render::RenderTarget("test");
*/
    //network::connectPorts(sky->outPortModelData, rp->inPortModelData);
    //network::connectPorts(rp->outPortRenderProgram, rt->inPortRenderProgram);

    lightRadiusPort = network::registerInPort("Composer", "LightRadius");
    lightRadiusPort->setDefaultValue(&fDef);

    lightHeightPort = network::registerInPort("Composer", "LightHeight");
    lightHeightPort->setDefaultValue(&fDef);

    lightSpeedPort = network::registerInPort("Composer", "LightSpeed");
    lightSpeedPort->setDefaultValue(&fDef);

    terrain = new Terrain();
    terrain->material->setTexture(0, store.getTexture("default.png")->handle());
    terrain->populateFromHeightMap("./data/heightmap1.png");

    harm = new qbz::Harmonics();
    harm->material->setTexture(0, store.getTexture("shit.png")->handle());
    harm->material->setTexture(1, store.getTexture("shit_NRM.png")->handle());
    harm->material->setTexture(2, store.getTexture("shit_SPEC.png")->handle());
    harm->translate(0.0f, 5.0f, 0.0f);

    sphere = world->loadMeshFile("data/sphere.x");
    sphere->setScale(2.0f, 2.0f, 2.0f);

    deferredRenderer = new DeferredRenderBuffer(QBZ_X_RES, QBZ_Y_RES);
    glPointSize(10.0);

}

void Composer::update() 
{
    world->update();

    float step = (2.0 * 3.14) / world->numLights;

    for (int ind=0; ind < world->numLights; ind++) {
        world->lightbuf[ind].position.y = *(float*)lightHeightPort->getValuePtr();
        world->lightbuf[ind].position.x = sin(step * ind + global_time->elapsed()/2500.0) * *(float*)lightRadiusPort->getValuePtr();
        world->lightbuf[ind].position.z = cos(step * ind + global_time->elapsed()/2500.0) * *(float*)lightRadiusPort->getValuePtr();
    }

}


std::string Composer::addComponent(ResourceType type, const std::string & identifier)
{
    switch(type) {
        case QBZ_RESOURCE_TEXTURE:
            qDebug() << "Add texture " << identifier.c_str();
            break;
    }

    std::string name = identifier + ";asdasd";
    return name;
}


void Composer::draw_embedded()
{
    /*
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    embed_quad[0]->material->setTexture(1, deferredRenderer->colorTexture);
    embed_quad[1]->material->setTexture(1, deferredRenderer->normTexture);
    embed_quad[2]->material->setTexture(1, deferredRenderer->posTexture);
    embed_quad[3]->material->setTexture(1, world->lightFBO->asTexture());

    for (int i=0; i<4; i++) {
        world->renderPrograms["projection2"]->drawObject(embed_quad[i]);        
    }
    */
}

void Composer::draw()
{

    //rt->Do();
    
    glDisable(GL_BLEND);
    glClearColor(0.4, 0.6, 0.9, 1.0);

    /* draw deferred objects to textures */

    deferredRenderer->begin();

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT, GL_FILL);

    world->renderPrograms["deferred0_billboard"]->drawObject(sky);
    world->renderPrograms["deferred0"]->drawObject(terrain);

    harm->update(0,0,0,0,3,3,2,3);
    world->renderPrograms["deferred0"]->drawObject(harm);

    deferredRenderer->end();



    /* compute ssao to FBO

    ssao_fbo->begin();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    ssao_fbo->rect->material->setTexture(1, deferredRenderer->colorTexture);
    world->projectionAreas[0]->material->setTexture(0, deferredRenderer->colorTexture);
    world->projectionAreas[0]->material->setTexture(1, deferredRenderer->posTexture);
    world->projectionAreas[0]->material->setTexture(2, deferredRenderer->normTexture);
    world->renderPrograms["SSAO"]->drawObject(world->projectionAreas[0]);
    ssao_fbo->end();

    shadowFbo->begin();

    glDisable(GL_CULL_FACE);


    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    qbz::Camera * cam = new Camera(glm::vec3(0.0f, 100.0f, 0.0f), glm::vec3(0.0f, 0.0f, -5.0f));
    world->renderPrograms["shadowmap0"]->drawObject(terrain, cam);
    world->renderPrograms["shadowmap0"]->drawObject(model, cam);

    shadowFbo->end();


    //shadowMapFbo->begin();
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    world->renderPrograms["shadowmap1"]->glProjectionMatrix = world->renderPrograms["shadowmap0"]->glProjectionMatrix;
    world->renderPrograms["shadowmap1"]->glModelViewMatrix = world->renderPrograms["shadowmap0"]->glModelViewMatrix;
    world->renderPrograms["shadowmap1"]->glViewMatrix = world->renderPrograms["shadowmap0"]->glViewMatrix;

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    world->projectionAreas[0]->material->setTexture(0, shadowFbo->asTexture());
    world->projectionAreas[0]->material->setTexture(1, deferredRenderer->posTexture);
    world->renderPrograms["shadowmap1"]->drawObject(world->projectionAreas[0]);
    //shadowMapFbo->end();
    */

    // render light map

    world->lightFBO->begin();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    world->lightFBO->rect->material->setTexture(1, deferredRenderer->posTexture);
    
    world->projectionAreas[0]->material->setTexture(0, deferredRenderer->colorTexture);
    world->projectionAreas[0]->material->setTexture(1, deferredRenderer->posTexture);
    world->projectionAreas[0]->material->setTexture(2, deferredRenderer->normTexture);
    world->renderPrograms["directional_light"]->drawObject(world->projectionAreas[0]);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);

    sphere->material->setTexture(0, deferredRenderer->colorTexture);
    sphere->material->setTexture(1, deferredRenderer->posTexture);
    sphere->material->setTexture(2, deferredRenderer->normTexture);

    for (int ind=0; ind < world->numLights; ++ind) {
        
        float dist = glm::distance(world->cameras[0]->_position, world->lightbuf[ind].position);

        if (dist < 7.0) {
            glCullFace(GL_FRONT);
            glPolygonMode(GL_BACK, GL_FILL); 
            glPolygonMode(GL_FRONT, GL_NONE);
        } else {
            glCullFace(GL_BACK);
            glPolygonMode(GL_FRONT, GL_FILL); 
            glPolygonMode(GL_BACK, GL_NONE);
        }
        
        sphere->setPosition(world->lightbuf[ind].position);
        world->renderPrograms["point_light"]->setRenderVariable("lightColor", world->lightbuf[ind].color);
        world->renderPrograms["point_light"]->setRenderVariable("lightPos", world->lightbuf[ind].position);
        world->renderPrograms["point_light"]->setRenderVariable("lightRadius", 2.0f);
        world->renderPrograms["point_light"]->drawObject(sphere);
        
        glDisable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
    }

    glDisable(GL_BLEND);
    world->lightFBO->end();    
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    world->projectionAreas[0]->material->setTexture(0, deferredRenderer->colorTexture);
    world->projectionAreas[0]->material->setTexture(1, world->lightFBO->asTexture());
    world->renderPrograms["projection"]->drawObject(world->projectionAreas[0]);
}


int t_x = 0; 
int t_y = 0;

void Composer::midiChanged(int channel, int value) 
{
    switch (channel) {
        case 2:

            break;
        case 14:
            //world->renderPrograms["point_light"]->setRenderVariable("shininess",
              //                                      (float)value);
            break;
        case 3:

            break;
        case 15:

            break;
        default:
            std::cout << "midi signal " << channel << " : " << value << std::endl;
            break;
    }
}

void Composer::keyPressed(int key) 
{
    
    switch (key) {
        case 'w':
        case 'W':
            world->cameras[0]->move(1.0f);
            break;
        case 's':
        case 'S':
            world->cameras[0]->move(-1.0f);
            break;
        case 'a':
        case 'A':
            world->cameras[0]->rotate(3.0f, 0.0f);
            break;
        case 'd':
        case 'D':
            world->cameras[0]->rotate(-3.0f, 0.0f);
            break;
        
            case ' ':
            //if (!animator->playing) {
            //    animator->play_animation(flash);
            //}
            break;
            
    }
    
}

void Composer::keyReleased(int key) {
}

void Composer::mousePressed(int x, int y, int key) {
    
}

void Composer::mouseMoved(int x, int y) {
}

void Composer::mouseReleased(int x, int y, int button) {
}

void Composer::mouseDragged(int x, int y, int button) {
    if (button == 2) {
        if (t_x == 0 && t_y == 0) {
            t_x = x;
            t_y = y;
        } else  {
            world->cameras[0]->rotate(x - t_x, y - t_y);
            t_x = x;
            t_y = y;
        }
    }
}
