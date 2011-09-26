#include "projectionarea.h"

using namespace qbz;

vertex* ProjectionArea::getTR() {
	return &vertices[TR];
}
vertex* ProjectionArea::getTL() {
	return &vertices[TL];
}
vertex* ProjectionArea::getBR() {
	return &vertices[BR];
}
vertex* ProjectionArea::getBL() {
	return &vertices[BL];
}

void ProjectionArea::moveTR(float x, float y) {
	vertices[TR].position.x = x;
	vertices[TR].position.y = y;
	this->keystone();
	this->mesh->update_vertex_buffer(vertices, buffer_size);
}

void ProjectionArea::moveTL(float x, float y) {
	vertices[TL].position.x = x;
	vertices[TL].position.y = y;
	this->keystone();
	this->mesh->update_vertex_buffer(vertices, buffer_size);
}

void ProjectionArea::moveBR(float x, float y) {
	vertices[BR].position.x = x;
	vertices[BR].position.y = y;
	this->keystone();
	this->mesh->update_vertex_buffer(vertices, buffer_size);
}

void ProjectionArea::moveBL(float x, float y) {
	vertices[BL].position.x = x;
	vertices[BL].position.y = y;
	this->keystone();
	this->mesh->update_vertex_buffer(vertices, buffer_size);
}

/* resize to actual pixel size hooked at TL corner */
void ProjectionArea::set_pixels(int x, int y) {

	if (x != 0) this->x_pixels = x;
	if (y != 0) this->y_pixels = y;
	
	float width = (2.0f / (float)1280) * (float)this->x_pixels;
	float height = (2.0f / (float)720) * (float)this->y_pixels;
	
	vertices[BL].position.x = vertices[TL].position.x;
	vertices[BL].position.y = vertices[TL].position.y - height;

	vertices[TR].position.x = vertices[TL].position.x + width;
	vertices[TR].position.y = vertices[TL].position.y;
	
	vertices[BR].position.x = vertices[TL].position.x + width;
	vertices[BR].position.y = vertices[TL].position.y - height;
	
	this->keystone();
	this->mesh->update_vertex_buffer(vertices, buffer_size);
}

void ProjectionArea::move_to(float x_pos, float y_pos) {
	float width = x_pos - vertices[TL].position.x;
	float height = y_pos - vertices[TL].position.y;
	
	vertices[BL].position.x += width;
	vertices[BL].position.y += height;

	vertices[BR].position.x += width;
	vertices[BR].position.y += height;
	
	vertices[TR].position.x += width;			
	vertices[TR].position.y += height;
	
	vertices[TL].position.x += width;
	vertices[TL].position.y += height;
	
	this->keystone();
	this->mesh->update_vertex_buffer(vertices, buffer_size);
}


void ProjectionArea::keystone() {
	
	float top_edge_length = vertices[TR].position.x - vertices[TL].position.x;
	float top_edge_scew = vertices[TR].position.y - vertices[TL].position.y;
	float bottom_edge_length = vertices[BR].position.x - vertices[BL].position.x;
	float bottom_edge_scew = vertices[BR].position.y - vertices[BL].position.y;
	
	float tl_x = vertices[TL].position.x;
	float tl_y = vertices[TL].position.y;
	float bl_x = vertices[BL].position.x;
	float bl_y = vertices[BL].position.y;
	
	int points_x = x_res + 1;
	int points_y = y_res + 1;

	float x_step = 1.0f / x_res;
	float y_step = 1.0f / y_res;
	
	int i =0;
	for (int row=0; row < points_y; row++) {
		for (int col=0; col < points_x; col++) {
			
			float x_slice = (float)col * x_step;
			float y_slice = (float)row * y_step;
			
			float top_reference_x = tl_x + (top_edge_length * x_slice);
			float top_reference_y = tl_y + (top_edge_scew * x_slice);
			float bottom_reference_x = bl_x + (bottom_edge_length * x_slice);
			float bottom_reference_y = bl_y + (bottom_edge_scew * x_slice);
			
			float x_delta = bottom_reference_x - top_reference_x;
			float y_delta = top_reference_y - bottom_reference_y;
			
			vertices[i].position.x = top_reference_x + x_delta - (x_delta*y_slice);
			vertices[i].position.y = bottom_reference_y + y_delta * y_slice;
			
			i++;
		}
	}
}

ProjectionArea::ProjectionArea(int tx, int ty, float bl_x, float bl_y, float tr_x, float tr_y) : Model(GL_QUADS) {

	this->x_res = 15;
	this->y_res = 15;
	this->x_pixels = tx;
	this->y_pixels = ty;
	this->texture_bl.position.x = bl_x;
	this->texture_bl.position.y = bl_y;
	this->texture_tr.position.x = tr_x;
	this->texture_tr.position.y = tr_y;
	
	this->quad_count = x_res * y_res;

	int points_x = x_res + 1;
	int points_y = y_res + 1;
	float x_step = 1.0f / x_res;
	float y_step = 1.0f / y_res;
	
	this->mesh->vertex_count = points_x * points_y;
	buffer_size = (this->mesh->vertex_count) * sizeof(vertex);
	vertices = (vertex*)malloc(buffer_size);
	if (!vertices) {
		std::cout << "cant allocate vertex buffer\n";
	} 
	memset(vertices, buffer_size, 0);
	GLuint element_count;
	
	int i=0;
	BL = 0;
	BR = x_res;
	TR = this->mesh->vertex_count-1;
	TL = TR - x_res; 
	
	for (int row=0; row < points_y; row++) {
		for (int col=0; col < points_x; col++) {
			float x = (float)col * x_step;
			float y = (float)row * y_step;
			
			vertices[i].position.x = (-0.5f) + x;
			vertices[i].position.y = (-0.5f) + y;
			vertices[i].position.z = 1.0f;
			
			vertices[i].texcoord.x = bl_x + (tr_x - bl_x) * x;
			vertices[i].texcoord.y = tr_y - (tr_y - bl_y) * y;
			
			vertices[i].normal.x = 0.0f;
			vertices[i].normal.y = 0.0f;
			vertices[i].normal.z = 1.0f;
			
			vertices[i].color.r = 1.0f;
			vertices[i].color.g = 1.0f;
			vertices[i].color.b = 1.0f;
			i++;
		}
	}
	
	switch (this->mesh->primitive_type) {
		case GL_POINTS:
			element_count = (GLuint)this->mesh->vertex_count;
			indices = (GLushort*) malloc(sizeof(GLushort) * element_count);
			for (GLuint ei=0; ei < element_count; ei++) {
				this->indices[ei] = ei;
			}			
			break;			
		
		case GL_LINE_LOOP:
		case GL_QUADS:
			element_count = (quad_count+1)*4;
			indices = (GLushort*) malloc(sizeof(GLushort) * element_count);
			if (!vertices) {
				std::cout << "cant allocate index buffer\n";
			}
			memset(indices, 0, sizeof(GLushort) * element_count);
			GLushort v=0;
			for (GLushort ind=0; ind < element_count - 4; ind+=4) {
				indices[ind] = v;
				indices[ind+1] = v+1;
				indices[ind+2] = v+points_x+1;
				indices[ind+3] = v+points_x;
				v++;
				if (!((v+1) % points_x)) 
					v++;
			}
			break;
	}
	
	this->mesh->set_vertex_buffer(vertices, buffer_size);
	this->mesh->set_element_buffer(indices, sizeof(GLushort) * (element_count));
	
	this->set_pixels(tx,ty);
};


void ProjectionArea::draw_outline(int xres, int yres) {
#ifdef QBZ_OPENFRAMEWORKS
	vertex* ptl = this->getTL();
	vertex* ptr = this->getTR();
	vertex* pbl = this->getBL();
	vertex* pbr = this->getBR();
	
	ofSetColor(255,255,255);
	ofLine((1.0f + ptl->position.x) * xres/2, (1.0f + ptl->position.y) * yres/2, (1.0f + ptr->position.x) * xres/2, (1.0f + ptr->position.y) * yres/2);
	ofLine((1.0f + ptr->position.x) * xres/2, (1.0f + ptr->position.y) * yres/2, (1.0f + pbr->position.x) * xres/2, (1.0f + pbr->position.y) * yres/2);
	ofLine((1.0f + pbr->position.x) * xres/2, (1.0f + pbr->position.y) * yres/2, (1.0f + pbl->position.x) * xres/2, (1.0f + pbl->position.y) * yres/2);
	ofLine((1.0f + pbl->position.x) * xres/2, (1.0f + pbl->position.y) * yres/2, (1.0f + ptl->position.x) * xres/2, (1.0f + ptl->position.y) * yres/2);
	
	if (true) ofSetColor(255,0,0);
	ofCircle((1.0f + ptl->position.x) * xres/2, (1.0f + ptl->position.y) * yres/2, 10);
	ofSetColor(255,255,255);
	
	if (true) ofSetColor(255,0,0);
	ofCircle((1.0f + ptr->position.x) * xres/2, (1.0f + ptr->position.y) * yres/2, 10);
	ofSetColor(255,255,255);
	
	if (true) ofSetColor(255,0,0);
	ofCircle((1.0f + pbl->position.x) * xres/2, (1.0f + pbl->position.y) * yres/2, 10);
	ofSetColor(255,255,255);
	
	if (true) ofSetColor(255,0,0);
	ofCircle((1.0f + pbr->position.x) * xres/2, (1.0f + pbr->position.y) * yres/2, 10);
#endif    
}
