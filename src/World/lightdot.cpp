#include "lightdot.h"

using namespace qbz;

LightDot::LightDot(float scale, glm::vec3 color) : Model(GL_POINTS) {
	
	buffer_size = sizeof(vertex) * 1;
        this->mesh.vertex_count = 1;

    for (int i=0; i<1; i++) {
        vertices[i].position.x = 0.0; 
        vertices[i].position.y = 0.0; 
        vertices[i].position.z = 0.0;
    
        vertices[i].color.r = color.r; 
        vertices[i].color.g = color.g; 
        vertices[i].color.b = color.b; 
    
        indices[i] = i;
    }
	
        this->mesh.set_vertex_buffer(vertices, buffer_size);
        this->mesh.set_element_buffer(indices, sizeof(indices));
}
/*
LightDot::setPosition(int index, glm::vec3 pos) {
    vertices[index].position.x = pos.x;
    vertices[index].position.y = pos.y;
    vertices[index].position.z = pos.z;    
}

LightDot::setColor(int index, glm::vec3 c) {
    vertices[index].color.r = c.r;
    vertices[index].color.g = c.g;
    vertices[index].color.b = c.b;    
}

LightDot::uploadChange() {
    this->mesh.update_vertex_buffer(vertices, buffer_size);
}
*/
