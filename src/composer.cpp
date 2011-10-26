
#include <iostream>
#include <cstdlib>

#include "composer.h"

#include "System/mainwindow.h"
#include "System/library.h"

#include "GL/renderprogram.h"
#include "GL/deferredrenderer.h"
#include "GL/fbo.h"
#include "GL/rendertarget.h"
#include "GL/skybox.h"
#include "GL/terrain.h"
#include "GL/finalout.h"

#include "World/camera.h"
#include "World/animator.h"
#include "World/world.h"
#include "World/projection_simple.h"
#include "World/projectionarea.h"
#include "World/harmonics.h"


using namespace qbz;

extern MainWindow* mainwindow;
extern QTime* global_time;

extern qbz::network::Network* gNetwork;

void Composer::setup()
{
    gNetwork->hasFinal = false;
    glPointSize(10.0);
    //projectionArea->move_to(-1.0, 1.0);
    //projectionAreas[0]->set_pixels();
    Camera * cam = Camera::getGlobalCamera();
}

void Composer::update() 
{
}


std::string Composer::addComponent(ResourceType type, const std::string & identifier)
{
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

    std::vector< std::pair< std::string, network::NetworkNode*> > renderTargets = network::getRenderTargetListHandle();
    std::vector< std::pair< std::string, network::NetworkNode*> >::iterator i;

    for (i=renderTargets.begin(); i!=renderTargets.end(); ++i)
    {
        i->second->Do();
    }

    qbz::network::NetworkNode* n = network::getFinalOut();
    if (n != NULL) {
        qbz::render::FinalOut* finalOut = reinterpret_cast<render::FinalOut*>(n);
        finalOut->Do();
    }
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
    Camera * cam = Camera::getGlobalCamera();

    switch (key) {
        case 'w':
        case 'W':
            cam->move(1.0f);
            break;
        case 's':
        case 'S':
            cam->move(-1.0f);
            break;
        case 'a':
        case 'A':
            cam->rotate(3.0f, 0.0f);
            break;
        case 'd':
        case 'D':
            cam->rotate(-3.0f, 0.0f);
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

void Composer::mouseDragged(int x, int y, int button)
{
    Camera * cam = Camera::getGlobalCamera();

    if (button == 2) {
        if (t_x == 0 && t_y == 0) {
            t_x = x;
            t_y = y;
        } else  {
            cam->rotate(x - t_x, y - t_y);
            t_x = x;
            t_y = y;
        }
    }
}
