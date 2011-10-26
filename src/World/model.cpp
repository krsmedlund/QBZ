/*
 *  model.cpp
 *  QBZ
 *
 *  Created by kristoffer smedlund on 11/07/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "World/model.h"
#include "Network/network.h"

using namespace qbz;

const std::string & Model::getType()
{
    return "Model";
}

static qbz::network::NetworkNode* ModelFactoryCreator(const std::string & nodeName)
{
    return new Model(nodeName);
}
static int foo = qbz::network::Factory::registerCreateFunction("Model", ModelFactoryCreator);


Model::Model(GLenum mesh_primitive)
{
    setPrimitive(mesh_primitive);
}

Model::Model(const std::string & _nodeName, GLenum mesh_primitive) : nodeName(_nodeName)
{
    network::registerNode(this, nodeName);
    inPorts["Texture"] = network::registerInPort(nodeName, "Texture");
    outPorts["ModelData"] = network::registerOutPort(nodeName, "ModelData", this, 1);
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

void Model::setPrimitive(GLenum mode) {
    this->mesh.primitive_type = mode;
}

void Model::setMesh(Mesh & _mesh) {
        this->mesh = mesh;
} 
