#include "qbz_skybox.h"

using namespace qbz;

SkyboxCube::SkyboxCube() : Model("Skybox", GL_QUADS) {
	
	this->mesh->vertex_count = 8;
        bool flip = false;
	buffer_size = sizeof(vertex) * 8;

	vertices[0].position.x = -1.0f; 
	vertices[0].position.y = -1.0f; 
	vertices[0].position.z = -1.0f;
	vertices[0].texcoord.x = 0.0f; 
	vertices[0].texcoord.y = (flip) ? 1.0 : 0.0;
	
	vertices[1].position.x = 1.0f; 
	vertices[1].position.y = -1.0f; 
	vertices[1].position.z = -1.0f;
	vertices[1].texcoord.x = 1.0f; 
	vertices[1].texcoord.y = (flip) ? 1.0 : 0.0f;
	
	vertices[2].position.x = 1.0f; 
	vertices[2].position.y = 1.0f; 
	vertices[2].position.z = -1.0f;
	vertices[2].texcoord.x = 1.0f; 
	vertices[2].texcoord.y = (flip) ? 0.0 : 1.0f;
	
	vertices[3].position.x = -1.0f; 
	vertices[3].position.y = 1.0f; 
	vertices[3].position.z = -1.0f;
	vertices[3].texcoord.x = 0.0f; 
	vertices[3].texcoord.y = (flip) ? 0.0 : 1.0f;
    
        vertices[4].position.x = -1.0f;
	vertices[4].position.y = -1.0f; 
	vertices[4].position.z = 1.0f;
	vertices[4].texcoord.x = 1.0f; 
	vertices[4].texcoord.y = (flip) ? 1.0 : 0.0;
	
	vertices[5].position.x = 1.0f; 
	vertices[5].position.y = -1.0f; 
	vertices[5].position.z = 1.0f;
	vertices[5].texcoord.x = 0.0f; 
	vertices[5].texcoord.y = (flip) ? 1.0 : 0.0f;
	
	vertices[6].position.x = 1.0f; 
	vertices[6].position.y = 1.0f; 
	vertices[6].position.z = 1.0f;
	vertices[6].texcoord.x = 0.0f; 
	vertices[6].texcoord.y = (flip) ? 0.0 : 1.0f;
	
	vertices[7].position.x = -1.0f; 
	vertices[7].position.y = 1.0f; 
	vertices[7].position.z = 1.0f;
	vertices[7].texcoord.x = 1.0f; 
	vertices[7].texcoord.y = (flip) ? 0.0 : 1.0f;
    
        indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;
    
        indices[4] = 7;
	indices[5] = 6;
	indices[6] = 5;
	indices[7] = 4;
    
        indices[8] = 3;
	indices[9] = 7;
	indices[10] = 4;
	indices[11] = 0;
    
        indices[12] = 1;
	indices[13] = 5;
	indices[14] = 6;
	indices[15] = 2;
    
        indices[16] = 3;
	indices[17] = 2;
	indices[18] = 6;
	indices[19] = 7;
    
        indices[20] = 4;
	indices[21] = 5;
	indices[22] = 1;
	indices[23] = 0;
    
	this->mesh->set_vertex_buffer(vertices, buffer_size);
        this->mesh->set_element_buffer(indices, sizeof(indices));
}
