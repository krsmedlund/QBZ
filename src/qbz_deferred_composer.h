//
//  qbz_deferred_composer.h
//  
//
//  Created by kristoffer smedlund on 08/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#define CHANNEL_COLOR_TEXTURE 0
#define CHANNEL_POSITION_TEXTURE 1
#define CHANNEL_NORMAL_TEXTURE 2
#define CHANNEL_DEPTH_TEXTURE 3

#define CHANNEL_WORLD0 0

#include "qbz_world.h"
#include "qbz_projectionarea.h"

namespace qbz {
    
    class DeferredComposer {
    public:
        DeferredComposer();
        
        GLuint textureInChannels[8];
        World* worldInChannels[0];
        
        void connect(GLuint handle, int id);
        void connect(World* handle, int id);
        
        void composeScene();
    };
    
};