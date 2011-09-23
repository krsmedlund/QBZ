//
//  qbz_light.h
//  
//
//  Created by kristoffer smedlund on 04/23/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef QBZ_LIGHT_H

#include "qbz.h"


/* Forward declares */

namespace qbz {
    
    class Model;
    
};

/* Class definition */

namespace qbz {
    
    struct Color {
        float r,g,b,a;
    };
    
    class Light {
    public:
      
        Light(qbz::Color, glm::vec3);


        void setDiffuseColor(float r=1.0f, float g=1.0f, float b=1.0f, float a=1.0f);
        void setDiffuseColor(qbz::Color);

        void setSpecularColor(float r=1.0f, float g=1.0f, float b=1.0f, float a=1.0f);
        void setSpecularColor(qbz::Color);

        
        void setPosition(float x=0.0f, float y=0.0f, float z=0.0f);
        void setPosition(glm::vec3 pos);
      
        void pointAt(float x=0.0f, float y=0.0f, float z=0.0f);
        void pointAt(glm::vec3 pos);
      
        void setTexture(GLuint texture_id);
        
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 target;
        
        qbz::Color diffuse_color;
        qbz::Color specular_color;
        
        float diffuse_intensity;
        float specular_intensity;
        
        qbz::Model *model;
        
        GLuint texture_id;
    };
};

#endif
