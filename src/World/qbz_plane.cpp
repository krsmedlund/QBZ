#include "qbz_plane.h"


void calculate_tangent(qbz::vertex *v1, qbz::vertex* v2, qbz::vertex* v3) {
    
    glm::vec2 uv1(v1->texcoord.x, v1->texcoord.y); 
    glm::vec2 uv2(v2->texcoord.x, v2->texcoord.y); 
    glm::vec2 uv3(v3->texcoord.x, v3->texcoord.y); 
    
    glm::vec3 p1(v1->position.x, v1->position.y, v1->position.z);
    glm::vec3 p2(v2->position.x, v2->position.y, v2->position.z);
    glm::vec3 p3(v3->position.x, v3->position.y, v3->position.z);
    
    glm::vec3 edge1 = p2 - p1;
    glm::vec3 edge2 = p3 - p1;
    
    glm::vec2 uv_edge1 = uv2 - uv1;
    glm::vec2 uv_edge2 = uv3 - uv1;
    
    float cpt = uv_edge1.y * uv_edge2.x - uv_edge1.x * uv_edge2.y;
    
    if (cpt != 0.0) {
        float mul = 1.0f / cpt;
        glm::vec3 tangent = glm::vec3(edge1 * -uv_edge2.y + edge2 * uv_edge2.y) * mul;
        glm::vec3 bitangent = glm::vec3(edge1 * -uv_edge2.x + edge2 * uv_edge2.x) * mul;
        
        glm::normalize(tangent);
        glm::normalize(bitangent);
        
        v1->tangent.x = tangent.x;
        v1->tangent.y = tangent.y;
        v1->tangent.z = tangent.z;
        v1->bitangent.x = bitangent.x;
        v1->bitangent.y = bitangent.y;
        v1->bitangent.z = bitangent.z;
        
        v2->tangent.x = tangent.x;
        v2->tangent.y = tangent.y;
        v2->tangent.z = tangent.z;
        v2->bitangent.x = bitangent.x;
        v2->bitangent.y = bitangent.y;
        v2->bitangent.z = bitangent.z;
        
        v3->tangent.x = tangent.x;
        v3->tangent.y = tangent.y;
        v3->tangent.z = tangent.z;
        v3->bitangent.x = bitangent.x;
        v3->bitangent.y = bitangent.y;
        v3->bitangent.z = bitangent.z;
    }
}


using namespace qbz;

Plane::Plane(int res) : Model(GL_TRIANGLES) {

	this->x_res = res;
	this->y_res = res;

	this->quad_count = x_res * y_res;

	int points_x = x_res + 1;
	int points_y = y_res + 1;
	
	float x_step = 1.0f / x_res;
	float y_step = 1.0f / y_res;
	
	this->mesh->vertex_count = points_x * points_y;
	int buffer_size = (this->mesh->vertex_count) * sizeof(vertex);
	vertices = (vertex*)malloc(buffer_size);
	if (!vertices) {
		std::cout << "cant allocate vertex buffer\n";
	} 
	memset(vertices, buffer_size, 0);
	GLuint element_count;
	
	int i=0;
	
	for (int row=0; row < points_y; row++) {
		for (int col=0; col < points_x; col++) {
			float x = (float)col * x_step;
			float y = (float)row * y_step;
			
			vertices[i].position.x = (-0.5f) + x;
			vertices[i].position.y = (-0.5f) + y;
			vertices[i].position.z = 0.0f;
			
			vertices[i].texcoord.x = x;
			vertices[i].texcoord.y = y;
			
			vertices[i].normal.x = 0.0f;
			vertices[i].normal.y = 1.0f;
			vertices[i].normal.z = 0.0f;
			
			vertices[i].color.r = 1.0f;
			vertices[i].color.g = 1.0f;
			vertices[i].color.b = 1.0f;
			i++;
		}
	}
	
    GLushort v = 0;
    switch (this->mesh->primitive_type) {
		case GL_POINTS:
			element_count = (GLuint)this->mesh->vertex_count;
			indices = (GLushort*) malloc(sizeof(GLushort) * element_count);
			for (GLuint ei=0; ei < element_count; ei++) {
				this->indices[ei] = ei;
			}			
			break;			

		case GL_TRIANGLES:
			element_count = quad_count*6;
			indices = (GLushort*)malloc(sizeof(GLushort) * element_count);
			if (!vertices) {
				std::cout << "cant allocate index buffer\n";
			}
			memset(indices, 0, sizeof(GLushort) * element_count);
			for (GLushort ind=0; ind < element_count; ind+=6) {

				indices[ind] = v;
				indices[ind+1] = v+points_x;
				indices[ind+2] = v+1;
                calculate_tangent(&vertices[v], &vertices[v+points_x], &vertices[v+1]);
				
                indices[ind+3] = v+1;
                indices[ind+4] = v+points_x;
                indices[ind+5] = v+points_x+1;
                calculate_tangent(&vertices[v+1], &vertices[v+points_x], &vertices[v+points_x+1]);
				
                v++;
				if (!((v+1) % points_x)) 
					v++;
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
			for (GLushort ind=0; ind < element_count - 4; ind+=4) {
				indices[ind] = v+1;
				indices[ind+1] = v;
				indices[ind+2] = v+points_x;
				indices[ind+3] = v+points_x+1;
				v++;
				if (!((v+1) % points_x)) 
					v++;
			}
			break;
	}
	
	this->mesh->set_vertex_buffer(vertices, buffer_size);
	this->mesh->set_element_buffer(indices, sizeof(GLushort) * (element_count));
	
}



