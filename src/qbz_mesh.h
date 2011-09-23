#ifndef _QBZ_MESH_H
#define _QBZ_MESH_H

#include "qbz.h"

namespace qbz {	
    
    // Forward declares
    
	class Mesh {
	public:
		Mesh(GLenum type=GL_TRIANGLES);
		void set_element_buffer(const GLushort* data, GLsizei len);
		void set_vertex_buffer(struct vertex* data, GLsizei len);
		void update_element_buffer(const GLushort* data, GLsizei len);
		void update_vertex_buffer(struct vertex* data, GLsizei len);
		
		vertex* get_vertex(int index);

		void bind();
		void release();
		
		GLenum primitive_type;
		
		glm::mat4 model_matrix;

		GLuint vertex_buffer;
		GLuint element_buffer;
		
		GLint vertex_count;
		GLint element_count;
		
		GLint vertex_buffer_data_length;
		GLint element_buffer_data_length;
	
	protected:
		const GLushort* element_buffer_data;
		vertex* vertex_buffer_data;
		
};};

#endif