//
//  qbz_deferredrenderer.h
//  
//
//  Created by kristoffer smedlund on 08/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "qbz.h"
#include "qbz_network.h"

namespace qbz 
{
    class DeferredRenderBuffer : public network::NetworkNode
    {
    public:
        DeferredRenderBuffer(int w, int h);
        GLuint fbo, depthBuffer, colorBuffer, posBuffer, normBuffer, colorTexture, posTexture, normTexture, depthTexture;
        
        void begin();
        void end();
    };

}
