#include "qbz_mesh.h"

using namespace qbz;

Mesh::Mesh(GLenum type) {
	this->model_matrix = glm::mat4(1.0);
	this->primitive_type = type;
}
 
void Mesh::set_element_buffer(const GLushort* data, GLsizei len) {
    glGenBuffers(1, &element_buffer);
	this->update_element_buffer(data, len);
}

void Mesh::update_element_buffer(const GLushort* data, GLsizei len) {
	this->element_buffer_data = data;
	this->element_buffer_data_length = len;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, len, data, GL_STREAM_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	
}

vertex* Mesh::get_vertex(int index) {
	return &vertex_buffer_data[index];
}

void Mesh::set_vertex_buffer(struct vertex* data, GLsizei len) {
    glGenBuffers(1, &vertex_buffer);
	this->update_vertex_buffer(data, len);
}

void Mesh::update_vertex_buffer(vertex* data, GLsizei len) {
	this->vertex_buffer_data = data;
	this->vertex_buffer_data_length = len;
	glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, len, data, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->element_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer);
}

void Mesh::release() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}