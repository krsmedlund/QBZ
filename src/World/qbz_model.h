/*
 *  qbz_model.h
 *  QBZ
 *
 *  Created by kristoffer smedlund on 11/07/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _QBZ_MODEL_H
#define _QBZ_MODEL_H

#include "qbz.h"
#include "qbz_shader.h"
#include "qbz_mesh.h"
#include "qbz_camera.h"
#include "qbz_network.h"

#define MAX_TEXTURE_SLOTS 128

namespace qbz {
	
    class Material {
    public:
        glm::vec4 diffuse;
        glm::vec4 specular;
        glm::vec4 ambient;
        glm::vec4 emission;
        float strength;
        float shininess;
        int two_sided;
        int wireframe;
        int max;
        GLenum fill_mode;
        GLboolean override_shader;
        
        unsigned int texture[MAX_TEXTURE_SLOTS];
        GLuint glowTexture;

        void setTexture(unsigned int slot, GLuint texture_id) { 
            this->texture[slot] = texture_id; 
        };
    };
    
    
    class Model : public network::NetworkNode
    {
    public:
        std::string nodeName;
        network::InPort *inPortTexture, *inPortPosition, *inPortScale, *inPortRotation;
        network::OutPort *outPortModelData;

        Model(GLenum mesh_primitive=GL_TRIANGLES);
        Model(const std::string & _nodeName, GLenum mesh_primitive=GL_TRIANGLES);
        Mesh * mesh;
        Material * material;
        glm::mat4 model_matrix;
        glm::mat4 rotate_matrix;
        glm::mat4 translate_matrix;
        glm::mat4 scale_matrix;
        glm::mat4 rotationMatrixInverse;
        glm::mat4 transformMatrixInverse;

        void set_primitive(GLenum);

        void set_mesh(Mesh*);

        void translate(float x, float y, float z);
        void setPosition(float x, float y, float z);
        void setPosition(const glm::vec3 &);

        void scale(float x, float y, float z);
        void setScale(float x, float y, float z);
        void setScale(const glm::vec3 &);

        void rotate(float angle, float x, float y, float z);
    };
}

#endif

