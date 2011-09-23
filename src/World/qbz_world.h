//
//  qbz_world.h
//  
//
//  Created by kristoffer smedlund on 05/03/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef QBZ_WORLD_H
#define QBZ_WORLD_H

#define MESH_FROM_FILE 0x01
#define MESH 0x02

#include <vector>

#include <assimp.h>
#include <aiPostProcess.h>
#include <aiScene.h>

#include "qbz.h"
#include "qbz_model.h"

namespace qbz {

    class RenderProgram;
    class Camera;
    class Projection_Simple;
    class ProjectionArea;
    class TextureLoader;
    class FBO;
    class LightDot;
    
    typedef struct {
        glm::vec3 position;
        glm::vec3 color;
    } s_light;
    
    class RenderParam {
    public:
        GLboolean override_shader;
        GLboolean override_fillmode;
    };
        
    
    class World {
    
    public:
        World();

        void update();
        void drawObjects(RenderParam* param=NULL);
        void drawLights();
        void drawGlow();
        void updateLightData();
        void composeScene();
        
        qbz::Model* addObject(short type, const char *name);
        GLuint addTexture(const char*);
        GLuint getTexture(const std::string & name);

        std::map<std::string, qbz::RenderProgram*> renderPrograms;
        std::map<std::string, GLuint> textures;
        
        std::vector<qbz::ProjectionArea*> projectionAreas;
        std::vector<qbz::Camera*> cameras;
        std::vector<qbz::Model*> objects;
        
        s_light lightbuf[1024];
        qbz::LightDot* lightModel[1024];
        
        int numLights;
        GLuint light_pixel_buffer, light_pixel_texture;
        qbz::FBO *glowFBO, *colorFBO, *lightFBO;

        static qbz::Model* loadMeshFile(const std::string & name);
        static qbz::Material* loadMaterial(const struct aiMaterial*);

    private:
        TextureLoader *textureLoader;


        
    };
};

#endif

