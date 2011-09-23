#ifndef _COOKIES_H
#define _COOKIES_H

#include "qbz_baseapp.h"
#include "qbz_model.h"

namespace qbz {
    class Animator;
};

class Cookies : public qbz::BaseApp {
		
public:
	qbz::Animator* animator;
    Cookies(qbz::Animator*);
	void setup();
	void update();
	void draw();
    void draw_shadow();
    
    
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
};

#endif