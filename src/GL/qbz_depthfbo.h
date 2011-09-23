#ifndef _QBZ_DEPTHFBO_H
#define _QBZ_DEPTHFBO_H

#include "qbz.h"

namespace qbz {
    
    class DepthFBO {
		public:
            DepthFBO(int w, int h);
            GLuint fbo, depthBuffer, depthTexture, colorTexture;

            void begin();
            void end();
            int w, h;
	};
};

#endif
