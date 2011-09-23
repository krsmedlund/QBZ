//
//  qbz_deferred_composer.cpp
//  
//
//  Created by kristoffer smedlund on 08/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "qbz_deferred_composer.h"

using namespace qbz;

DeferredComposer::DeferredComposer() {
    textureInChannels[0] = 0;
    textureInChannels[1] = 0;
    textureInChannels[2] = 0;
    textureInChannels[3] = 0;
    textureInChannels[4] = 0;
}

void DeferredComposer::connect(GLuint handle, int id) {
    textureInChannels[id] = handle;
}

void DeferredComposer::connect(World* handle, int id) {
    worldInChannels[id] = handle;
}

void DeferredComposer::composeScene() {
    worldInChannels[0]->projectionAreas[0]->material->setTexture(0, textureInChannels[0]);
    worldInChannels[0]->projectionAreas[0]->material->setTexture(1, textureInChannels[1]);
    worldInChannels[0]->projectionAreas[0]->material->setTexture(2, textureInChannels[2]);
    worldInChannels[0]->projectionAreas[0]->material->setTexture(3, worldInChannels[0]->light_pixel_texture);
    worldInChannels[0]->projectionAreas[0]->material->setTexture(4, textureInChannels[3]);

    worldInChannels[0]->composeScene();
}
