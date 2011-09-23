/*
 *  qbz_model.cpp
 *  QBZ
 *
 *  Created by kristoffer smedlund on 11/07/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "qbz_model.h"
#include "qbz_network.h"

using namespace qbz;



Model::Model(GLenum mesh_primitive)
{
    this->mesh = new Mesh(mesh_primitive);
    this->material = new Material();
}

Model::Model(const std::string & _nodeName, GLenum mesh_primitive) : nodeName(_nodeName)
{
    this->mesh = new Mesh(mesh_primitive);
    this->material = new Material();
    network::registerNode(this, nodeName);
    inPortTexture = network::registerInPort(nodeName, "Texture");
    outPortModelData = network::registerOutPort(nodeName, "ModelData", this, 1);
    std::cout << _nodeName << " : " << outPortModelData->getValuePtr() << std::endl;
}


void Model::translate(float x, float y, float z) {
	this->translate_matrix = glm::translate(this->translate_matrix, glm::vec3(x,y,z));
}

void Model::setPosition(float x, float y, float z) {
    glm::mat4 tmp;
	this->translate_matrix = glm::translate(tmp, glm::vec3(x,y,z));
}
void Model::setPosition(const glm::vec3 & newPos) {
    glm::mat4 tmp;
    this->translate_matrix = glm::translate(tmp, newPos);
}

void Model::setScale(float x, float y, float z) {
    glm::mat4 tmp;
	this->scale_matrix = glm::scale(tmp, glm::vec3(x,y,z));
}

void Model::setScale(const glm::vec3 & newScale) {
    glm::mat4 tmp;
    this->scale_matrix = glm::scale(tmp, newScale);
}

void Model::scale(float x, float y, float z) {
	this->scale_matrix = glm::scale(this->scale_matrix, glm::vec3(x,y,z));
}

void Model::rotate(float angle, float x, float y, float z) {
	this->rotate_matrix = glm::rotate(this->rotate_matrix, angle, glm::vec3(x, y, z));
}

void Model::set_primitive(GLenum mode) {
    this->mesh->primitive_type = mode;
}

void Model::set_mesh(Mesh* mesh) {
	this->mesh = mesh;
} 
