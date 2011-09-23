#ifndef QBZ_PROJECTIONMAPPER_H
#define QBZ_PROJECTIONMAPPER_H

#include "qbz_baseapp.h"
#include "qbz_fbo.h"
#include "qbz_projectionarea.h"
#include "qbz_projection_simple.h"
#include "qbz_playlist.h"

namespace qbz {
    class ProjectionMapper : public BaseApp {
public:
	void setup();
	void update();
	void draw();
	void draw_embedded();
	
	void add_scene(qbz::Playlist* pl, BaseApp* scene, QString renderer, int x, int y);
	void select_projection(int id);
	//void add_movie(qbz::Playlist* pl, const char* filename, int loop_state=OF_LOOP_NORMAL);
	
	std::vector<qbz::ProjectionArea*> projection_list;
	std::vector<qbz::FBO*> fbo_list;
	std::vector <qbz::Playlist*> playlists;
	
	qbz::ProjectionArea* selected_projection;
	qbz::Projection_Simple* edit;
	qbz::Camera* cam;
	qbz::BaseApp* current_scene;
	
	void keyReleased(int key);
	void mousePressed(int x, int y, int button);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void keyPressed(int key);
	void mouseReleased(int x, int y, int button);


	
	bool is_embedded;
};
};

#endif