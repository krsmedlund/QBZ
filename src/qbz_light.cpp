//
//  qbz_light.cpp
//  
//
//  Created by kristoffer smedlund on 04/23/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "qbz_light.h"

using namespace qbz;

Light::Light(Color color, glm::vec3 position) {
    this->diffuse_color.r = color.r;
    this->diffuse_color.g = color.g;
    this->diffuse_color.b = color.b;
    this->diffuse_color.a = color.a;

    this->specular_color.r = color.r;
    this->specular_color.g = color.g;
    this->specular_color.b = color.b;
    this->specular_color.a = color.a;

    this->position = position;
    
}

void Light::setPosition(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Light::setPosition(glm::vec3 pos) {
    this->position = pos;
}

void Light::setTexture(GLuint texture_id) {
    this->texture_id = texture_id;
}

void Light::setDiffuseColor(float r, float g, float b, float a) {
    this->diffuse_color.r = r;
    this->diffuse_color.g = g;
    this->diffuse_color.b = b;
    this->diffuse_color.a = a;
}

void Light::setDiffuseColor(Color color) {
    this->diffuse_color.r = color.r;
    this->diffuse_color.g = color.g;
    this->diffuse_color.b = color.b;
    this->diffuse_color.a = color.a;
}

void Light::setSpecularColor(float r, float g, float b, float a) {
    this->specular_color.r = r;
    this->specular_color.g = g;
    this->specular_color.b = b;
    this->specular_color.a = a;
}

void Light::setSpecularColor(Color color) {
    this->specular_color.r = color.r;
    this->specular_color.g = color.g;
    this->specular_color.b = color.b;
    this->specular_color.a = color.a;
}


void Light::pointAt(glm::vec3 target) {
    this->target = target;
}