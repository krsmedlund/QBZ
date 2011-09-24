#include "qbz_fbo.h"

#include "GL/qbz_renderprogram.h"
#include "World/qbz_projection_simple.h"

using namespace qbz;

FBO::FBO(int w, int h, bool depth) {
    this->w = w;
    this->h = h;
    this->isDepth = depth;
    if (depth) {
        QGLFramebufferObjectFormat fmt;
        fmt.setAttachment(QGLFramebufferObject::Depth);
        fmt.setInternalTextureFormat(GL_DEPTH_COMPONENT);
        fbo = new QGLFramebufferObject(w, h, fmt);
        if (QGLFramebufferObject::Depth != fbo->attachment()) {
            qDebug() << "FAIL";
        }
    } else fbo = new QGLFramebufferObject(w, h);

	if (!fbo->isValid()) {
		std::cout << "FBO failed!\n";
	} else {
		int h = fbo->size().height();
		int w = fbo->size().width();
	}
    rect = new Projection_Simple(false);
}

void FBO::setChannel(int pp, float* p) { 
    //this->post_processors.at(pp)->setChannel(pp, p);
}


int FBO::addPostProcessor(QString name) {
    RenderProgram* s = new RenderProgram(name, true);
        this->post_processors.push_back(s);
	if (this->post_processors.size() == 1) {
		fbo_2 = new QGLFramebufferObject(this->w, this->h);
		if (!fbo_2->isValid()) {
			std::cout << "FBO2 failed!\n";
		} else {
			int h = fbo_2->size().height();
			int w = fbo_2->size().width();
                        //std::cout << "FBO2 created with size " <<  w << " :" << h << "\n";
		}
    }
    return this->post_processors.size();
}

unsigned int FBO::asTexture() {
	return this->fbo->texture();
}

void FBO::begin() {
	fbo->bind();	
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void FBO::end() {
	fbo->release();
    for(int i=0; i < this->post_processors.size(); i++) {
        this->fbo_2->bind();
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        this->post_processors.at(i)->begin();
        this->rect->material->setTexture(0, fbo->texture());
        this->post_processors.at(i)->drawObject(this->rect, this->cam);        
        this->post_processors.at(i)->end();
		this->fbo_2->release();
		
		tmp = fbo;
		fbo = fbo_2;
		fbo_2 = tmp;
	}
}
