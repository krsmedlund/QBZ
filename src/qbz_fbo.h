#ifndef _QBZ_FBO_H
#define _QBZ_FBO_H

#include "qbz.h"

namespace qbz {
    
    class RenderProgram;
    class Projection_Simple;
    class Camera;
    
	class FBO {
		public:
        Camera* cam;
            FBO(int w, int h, bool depth=false);
			QGLFramebufferObject* fbo;
			QGLFramebufferObject* fbo_2;
			QGLFramebufferObject* tmp;
			QGLFramebufferObject* bound_fbo;
		
            void begin();
			void end();
        
            bool isDepth;

			unsigned int asTexture();
			int addPostProcessor(QString name);
            void setChannel(int pp, float* p);
	
			std::vector<qbz::RenderProgram*> post_processors;
			int w, h;
			qbz::Projection_Simple* rect;
	};
};

#endif
