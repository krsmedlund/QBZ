#include "projection_simple.h"

using namespace qbz;

Projection_Simple::Projection_Simple(bool flip, float scale) : Model(GL_QUADS) {
	
	buffer_size = sizeof(vertex) * 4;
        this->mesh.vertex_count = 4;

	vertices[0].position.x = scale * -1.0f; 
	vertices[0].position.y = scale * -1.0f; 
	vertices[0].position.z = -1.0f;
	vertices[0].texcoord.x = 0.0f; 
	vertices[0].texcoord.y = (flip) ? 1.0 : 0.0;
	
	vertices[1].position.x = scale *  1.0f; 
	vertices[1].position.y = scale *  -1.0f; 
	vertices[1].position.z = -1.0f;
	vertices[1].texcoord.x = 1.0f; 
	vertices[1].texcoord.y = (flip) ? 1.0 : 0.0f;
	
	vertices[2].position.x = scale * 1.0f; 
	vertices[2].position.y = scale * 1.0f; 
	vertices[2].position.z = -1.0f;
	vertices[2].texcoord.x = 1.0f; 
	vertices[2].texcoord.y = (flip) ? 0.0 : 1.0f;
	
	vertices[3].position.x = scale * -1.0f; 
	vertices[3].position.y = scale * 1.0f; 
	vertices[3].position.z = -1.0f;
	vertices[3].texcoord.x = 0.0f; 
	vertices[3].texcoord.y = (flip) ? 0.0 : 1.0f;
	
    vertices[0].color.r = 1.0;
    vertices[1].color.r = 1.0;
    vertices[2].color.r = 1.0;
    vertices[3].color.r = 1.0;
    
    vertices[0].color.g = 0.0;
    vertices[1].color.g = 0.0;
    vertices[2].color.g = 0.0;
    vertices[3].color.g = 0.0;
    
    vertices[0].color.b = 1.0;
    vertices[1].color.b = 1.0;
    vertices[2].color.b = 1.0;
    vertices[3].color.b = 1.0;
    
    indices[0] = 3;
	indices[1] = 2;
	indices[2] = 1;
	indices[3] = 0;
	
        this->mesh.set_vertex_buffer(vertices, buffer_size);
        this->mesh.set_element_buffer(indices, sizeof(indices));
}
