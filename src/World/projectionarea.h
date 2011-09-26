#ifndef _QBZ_PROJECTIONAREA_H
#define _QBZ_PROJECTIONAREA_H

#include "qbz.h"
#include "World/model.h"

namespace qbz {
    
    class RenderProgram;
	
	class ProjectionArea : public Model {

	public:
		ProjectionArea(int tx, int ty, float bl_x=0.0f, float bl_y=0.0f, float tr_x=1.0f, float tr_y=1.0f);
		
		void moveTR(float x, float y);
		void moveTL(float x, float y);
		void moveBL(float x, float y);
		void moveBR(float x, float y);
		
		vertex* getTR();
		vertex* getTL();
		vertex* getBR();
		vertex* getBL();

		void keystone();
		void move_to(float, float);
		void set_pixels(int x=0, int y=0);
		void draw_outline(int, int);

    private:
		
        /* mesh data */
		
        vertex* vertices;
		GLushort* indices;
		int x_res, y_res, quad_count, BL, BR, TR, TL, buffer_size;
		
		
        /* texture data */
		
        GLuint texture_id;
		int x_pixels, y_pixels;
		vertex texture_bl;
		vertex texture_tr;
        
        /* shader */
        
        RenderProgram* render_program;
		
	};
	
};

#endif
