#include "qbz_projectionmapper.h"
#include "mainwindow.h"
#include "cookies.h"

class BlackScene : public qbz::BaseApp {
	void draw() { glClearColor(0,0,0,0); glClear(GL_COLOR_BUFFER_BIT); }
};

extern MainWindow* mainwindow;

using namespace qbz;

float d;
int selected=0;
bool bl, br, tr, tl = false;
bool setup_q = false;
bool single_scene = false;	

void ProjectionMapper::select_projection(int id) {
	//this->selected_projection = this->scenes.at(0)->projection_list.at(id);
}


ProjectionArea* current_area;
FBO* current_fbo;

void ProjectionMapper::add_scene(Playlist* pl, BaseApp* scene, QString renderer, int x, int y) {
	
    /* give the scene something to render in */
	
    if (pl->playlist.size() < 1) {
		FBO* framebuffer = new FBO(x, y);
	
		/* give the scene a projection to show in */
		ProjectionArea* area = new ProjectionArea(
											x , y,							// texture height and width
											0.0f, 0.0f,						// texture bottom left corner
											1.0f, 1.0f						// texture top right corner
											);
		area->set_shader(renderer);
		this->projection_list.push_back(area);
		this->fbo_list.push_back(framebuffer);
		pl->set_area(this->projection_list.size() - 1);
		pl->set_fbo(this->fbo_list.size() - 1);
	}
	this->current_scene = scene;
	scene->setup();
	pl->add(scene);	
}

void ProjectionMapper::setup() {
	
	cam = new Camera(0.0f, 0.0f, 10.0f);
	
	Playlist* pl = new Playlist();
	this->playlists.push_back(pl);
	
	edit = new qbz::Projection_Simple(true);
	edit->set_shader("projection");
	
	glEnable(GL_POINT_SMOOTH);
	glPointSize(10.0f);
}

void ProjectionMapper::update() {
}


void ProjectionMapper::draw_embedded() {
	glClearColor(0.9, 0.7, 0.5, 0.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	
}


void ProjectionMapper::draw() {
	glClearColor(0.4, 0.5, 0.7, 1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
    //this->playlists.at(0)->current->update();
	//this->playlists.at(0)->current->draw();
	
	//return;
	
	//if (!this->is_embedded) {
		//for (unsigned int i=0; i < this->playlists.size(); i++) {
			
			current_scene = this->playlists.at(0)->current;
			current_fbo = this->fbo_list.at(this->playlists.at(0)->fbo);
			current_area = this->projection_list.at(this->playlists.at(0)->area);

    
			/* ready the scene for render */
			
			current_scene->update();
			
			/* bind framebuffer to render the scene in */
			
			current_fbo->begin();
			
			/* clear the framebuffer */
			
			glClearColor(0.0, 0.0, 0.0, 0.0);
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			
			/* update and draw the scene */

			current_scene->draw();
			
			/* release the framebuffer */
			
			current_fbo->end();
			
			/* draw the scenes projection */
			
			current_area->set_texture0(current_fbo->texture());
			current_area->draw();
		//}
	//}
	/*
	if (setup_q) 
        this->projection_list.at(
                            this->playlists.at(selected)->area
                                 )->draw_outline(ofGetWidth(), ofGetHeight());
	*/
}	
void ProjectionMapper::keyPressed(int key) {
	if (!setup_q) {
		this->current_scene->keyPressed(key);
	}
}

int playlist_index = 0;

void ProjectionMapper::keyReleased(int key) {
	
	if (!setup_q) {
		switch (key) {
			case 'q':
				setup_q = !setup_q;
				break;
			default:
				this->current_scene->keyReleased(key);
				break;
		}
	}
	
	if (setup_q) {
	switch (key) {
		case '1':
			bl = true;
			br = tr = tl = false;
			break;
		case '2':
			br = true;
			bl = tr = tl = false;
			break;
		case '3':
			tr = true;
			br = bl = tl = false;
			break;
		case '4':
			tl = true;
			br = tr = bl = false;
			break;
		case '\t':
			selected++;
			if (selected >= this->playlists.size()) selected = 0;
			break;
		case 'q':
			setup_q = !setup_q;
			break;

		case 'n':
			this->playlists.at(0)->next();
			this->playlists.at(1)->next();
			this->playlists.at(2)->next();
			break;
			
		case 'b':
			this->playlists.at(0)->prev();
			this->playlists.at(1)->prev();
			this->playlists.at(2)->prev();
			break;
			
		case 'p':
			if (setup_q) this->projection_list.at(this->playlists.at(selected)->area)->set_pixels();
			break;
		default:
			break;
	}
	}
}

void ProjectionMapper::mousePressed(int x, int y, int key) {
	
	if (!setup_q) {
		this->current_scene->mousePressed(x, y, key);
		return;
	}
	
	float fx = -1.0f + (2.0f/(float)ofGetWidth()) * x;
	float fy = -1.0f + (2.0f/(float)ofGetHeight()) * y;

	if ( key == 2 ) {
		this->projection_list.at(this->playlists.at(selected)->area)->move_to(fx, fy);
		return;
	} else {
	
		if (tr) { 
			this->projection_list.at(this->playlists.at(selected)->area)->moveTR(fx, fy);
		}	
		else if (tl) { 
			this->projection_list.at(this->playlists.at(selected)->area)->moveTL(fx, fy);
		}
		else if (br) { 
			this->projection_list.at(this->playlists.at(selected)->area)->moveBR(fx, fy);
		}	
		else if (bl) { 
			this->projection_list.at(this->playlists.at(selected)->area)->moveBL(fx, fy);
		}
	}
}

void ProjectionMapper::mouseMoved(int x, int y) {
	if (!setup_q) {
		this->current_scene->mouseMoved(x, y);
		return;
	}
}
void ProjectionMapper::mouseReleased(int x, int y, int button) {
	if (!setup_q) {
		this->current_scene->mouseReleased(x, y, button);
		return;
	}
}

void ProjectionMapper::mouseDragged(int x, int y, int button) {
	
    this->current_scene->mouseDragged(x, y, button);
    return;
	
	if (!setup_q) {
		this->current_scene->mouseDragged(x, y, button);
		return;
	}
	
	float fx = -1.0f + (2.0f/(float)ofGetWidth()) * x;
	float fy = -1.0f + (2.0f/(float)ofGetHeight()) * y; 
	
	if ( button == 2 ) {
		this->projection_list.at(this->playlists.at(selected)->area)->move_to(fx, fy);
		return;
	}	

	if (tr) { 
		this->projection_list.at(this->playlists.at(selected)->area)->moveTR(fx, fy);
	} else if (tl) { 
		this->projection_list.at(this->playlists.at(selected)->area)->moveTL(fx, fy);
	} else if (br) { 
		this->projection_list.at(this->playlists.at(selected)->area)->moveBR(fx, fy);
	} else if (bl) { 
		this->projection_list.at(this->playlists.at(selected)->area)->moveBL(fx, fy);
	}
}
