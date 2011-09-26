/*
 *  qbz_baseapp.h
 *  QBZ
 *
 *  Created by kristoffer smedlund on 10/30/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _QBZ_BASEAPP_H
#define _QBZ_BASEAPP_H

#include "GL/fbo.h"
#include "World/projectionarea.h"

namespace qbz {
	class BaseApp 
#ifdef QBZ_OPENFRAMEWORKS
    : public ofBaseApp 
#endif    
    {
	public:
		virtual void setup() {}
		virtual void update() {}
		virtual void draw() {}
        virtual void draw_shadow() {}
		virtual void draw_embedded() {}
		virtual void exit() {}
		virtual void stop() {}
		virtual void play() {}
		virtual float getPosition() {}
		virtual void setPosition(float pos) {}
		
		virtual void windowResized(int w, int h){}
		virtual void keyPressed( int key ){}
		virtual void keyReleased( int key ){}
		
		virtual void mouseMoved( int x, int y ){}
		virtual void mouseDragged( int x, int y, int button ){}
		virtual void mousePressed( int x, int y, int button ){}
		virtual void mouseReleased(){}
		virtual void mouseReleased(int x, int y, int button ){}
		virtual void midiChanged(int channel, int value) {}
        
		bool is_embedded;
        bool uses_shadow;
		QString name;
		
		int fbo;
		void set_fbo(int f) { this->fbo = f; };

		int area;
		void set_area(int a) { this->area = a; };
};};

#endif
