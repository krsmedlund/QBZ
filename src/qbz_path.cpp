//
//  qbz_path.cpp
//  qbz2
//
//  Created by kristoffer smedlund on 08/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "qbz_path.h"

Path::Path() {
}

glm::vec3 * Path::getPos(float factor) {
}

void Path::tick() {
}

ManualPath::ManualPath() {
}

ManualPath::addPos(const glm::vec3 & pos) {
}
        
glm::vec3 * ManualPath::getPos(float factor) {
}
        
    
CirclePath(float radius, float height, float speed);
        void setRadius(float radius);
        void setHeight(float height);
        void setSpeed(float speed);
        
        glm::vec3 * getPos(float factor);
        void tick();
