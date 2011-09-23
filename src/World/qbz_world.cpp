//
//  qbz_world.cpp
//  
//
//  Created by kristoffer smedlund on 05/03/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "qbz_world.h"
#include "qbz_renderprogram.h"
#include "qbz_light.h"
#include "qbz_projection_simple.h"
#include "qbz_projectionarea.h"
#include "qbz_tgatexture.h"
#include "qbz_fbo.h"
#include "qbz_lightdot.h"

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

using namespace qbz;
using namespace std;

World::World() {

    this->textureLoader = new TextureLoader();
    
    this->projectionAreas.push_back(new ProjectionArea(QBZ_X_RES, QBZ_Y_RES, 0.0f, 1.0f, 1.0f, 0.0f));
    this->projectionAreas[0]->move_to(-1.0, 1.0);
    this->projectionAreas[0]->set_pixels();

    this->cameras.push_back(Camera::getGlobalCamera());
    
    this->renderPrograms["deferred0"] = new RenderProgram("deferred0");
    this->renderPrograms["deferred0_billboard"] = new RenderProgram("deferred0_billboard");
    this->renderPrograms["shadowmap0"] = new RenderProgram("shadowmap0");
    this->renderPrograms["shadowmap1"] = new RenderProgram("shadowmap1");
    this->renderPrograms["glow"] = new RenderProgram("glow");
    this->renderPrograms["projection"] = new RenderProgram("projection");
    this->renderPrograms["projection2"] = new RenderProgram("projection");
    this->renderPrograms["SSAO"] = new RenderProgram("SSAO");
    this->renderPrograms["directional_light"] = new RenderProgram("directional_light");
    this->renderPrograms["point_light"] = new RenderProgram("point_light");
    this->renderPrograms["wireframe"] = new RenderProgram("wireframe");

    this->numLights = 12;
    
    for (int ind=0; ind<numLights; ind++) {
        this->lightbuf[ind].position = glm::vec3(0);
        this->lightbuf[ind].color = glm::vec3(
                                        (float)rand()/(float)RAND_MAX,
                                        (float)rand()/(float)RAND_MAX,
                                        (float)rand()/(float)RAND_MAX);
        this->lightModel[ind] = new LightDot(1.0, glm::vec3(this->lightbuf[ind].color.r, this->lightbuf[ind].color.g, this->lightbuf[ind].color.b));

    }

    glGenTextures(1, &light_pixel_texture);
    glBindTexture(GL_TEXTURE_2D, light_pixel_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F_ARB, 2, numLights, 0, GL_RGB, GL_FLOAT, (GLvoid*)&lightbuf[0]);
    
    glGenBuffers(1, &light_pixel_buffer);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, light_pixel_buffer);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, numLights * sizeof(s_light), (GLfloat*)&lightbuf[0], GL_STREAM_DRAW);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 2, numLights, GL_RGB, GL_FLOAT, 0);

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    this->glowFBO = new FBO(QBZ_X_RES, QBZ_Y_RES);
    this->glowFBO->addPostProcessor("blur_vertical");
    this->glowFBO->addPostProcessor("blur_vertical");
    
    this->colorFBO = new FBO(QBZ_X_RES, QBZ_Y_RES);
    this->colorFBO->addPostProcessor("depthoffield_U");
    this->colorFBO->addPostProcessor("depthoffield_V");
    
    this->lightFBO = new FBO(QBZ_X_RES, QBZ_Y_RES);
    //this->lightFBO->addPostProcessor("color_separate_cmyk");
    //this->lightFBO->addPostProcessor("depthoffield_U");
    //this->lightFBO->addPostProcessor("depthoffield_V");
    
    int num;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS_ARB, &num);
    std::cout << "max " << num << " textures." << std::endl;
}

void World::composeScene() {
    

    
}

void World::drawGlow() {
   
    this->glowFBO->begin();
    glClearColor(0.2, 0.0, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    for(vector<Model*>::iterator it = this->objects.begin(); it != this->objects.end(); ++it) {
        this->renderPrograms["glow"]->drawObject(*it, this->cameras[0]);
    }
    this->glowFBO->end();
   
    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE); 
    glBlendFunc(GL_ONE, GL_ONE);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}

void World::drawLights() {

    for (int i=0; i<numLights; i++) {
        this->lightModel[i]->setPosition(this->lightbuf[i].position);
        this->renderPrograms["deferred0_billboard"]->drawObject(this->lightModel[i]);
    }
}

void World::updateLightData() {
}

void World::drawObjects(RenderParam* param) {
    for(vector<Model*>::iterator it = this->objects.begin(); it != this->objects.end(); ++it) {
        this->renderPrograms["deferred0"]->drawObject(*it);
    }
}

void World::update() {
    return;
}

GLuint World::addTexture(const char* name) {
#if 0
    std::string n(name);
    QString load("data/");
    load.append(name);
    GLuint tex = this->textureLoader->textureFromFile(load);
    this->textures[n] = tex;
    return tex;
#endif
}

GLuint World::getTexture(const std::string & name) {
    return this->textures[name];
}

Model* World::addObject(short type, const char* name) {
    
    Model* asset;

    switch (type) {
        case MESH_FROM_FILE:
            if (NULL != (asset = this->loadMeshFile(name))) {
                this->objects.push_back(asset);
                return asset;
            }
            break;
        default:
            break;
    }
}

Material* World::loadMaterial(const struct aiMaterial *mtl)
{
    Material* mat = new Material();
    
    GLenum fill_mode;
    int ret1, ret2;
    struct aiColor4D diffuse;
    struct aiColor4D specular;
    struct aiColor4D ambient;
    struct aiColor4D emission;
    float shininess, strength;
    int two_sided;
    int wireframe;
    unsigned int max;
    
    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
        mat->diffuse = glm::vec4(diffuse.r, diffuse.g, diffuse.b, diffuse.a);
        
    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
        mat->specular = glm::vec4(specular.r, specular.g, specular.b, specular.a);
    
    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
        mat->diffuse = glm::vec4(ambient.r, ambient.g, ambient.b, ambient.a);
    
    //if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
    //    mat->diffuse = glm::vec4(emission.r, emission.g, emission.b, emission.a);
    
    max = 1;
    ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
    
    max = 1;
    ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);

    if((ret1 == AI_SUCCESS) && (ret2 == AI_SUCCESS)) {
        mat->strength = strength;
        mat->shininess = shininess;
    } else {
        mat->shininess = 0.0f;
        mat->strength = 0.0f;
        mat->specular = glm::vec4(0.0f);
    }
    
    max = 1;
    if(AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
        mat->fill_mode = wireframe ? GL_LINE : GL_FILL;
    else
        mat->fill_mode = GL_FILL;
    
    max = 1;
    if((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
        mat->two_sided = false;
    else
        mat->two_sided = true;
    
    return mat;
}


Model* World::loadMeshFile(const std::string & filename)
{
    vertex* vertices;
    GLushort* indices;
    GLuint scene_list = 0;
    const aiScene* scene = NULL;
    aiVector3D scene_min, scene_max, scene_center;
    static float angle = 0.f;
    GLenum face_mode;

    const aiMesh* mesh;

    //Assimp::Importer importer;
    scene = aiImportFile(filename.c_str(),
                              aiProcess_CalcTangentSpace
                              | aiProcess_Triangulate
                              | aiProcess_GenNormals
                              | aiProcess_FixInfacingNormals);
	
    if (scene) {

        std::cout << "Loading model " << filename
                  << "\n\thas meshes " << scene->HasMeshes()
                  << "\n\thas cameras " << scene->HasCameras()
                  << "\n\thas textures " << scene->HasTextures()
                  << "\n\thas materials " << scene->HasMaterials()
                  << "\n\thas animations " << scene->HasAnimations()
                  << std::endl;

        int v_counter = 0;
		mesh = scene->mMeshes[0];
        vertices = new qbz::vertex[mesh->mNumVertices];
		indices = new GLushort[mesh->mNumFaces * 3];
        

        //vertices = VBO::allocateVertices(mesh->mNumVertices);


        /* set vertex data */
        
        for (unsigned int index=0; index < mesh->mNumVertices; index++) {
            
            if (mesh->HasPositions()) {
                vertices[index].position.x = mesh->mVertices[index].x;
                vertices[index].position.y = mesh->mVertices[index].y;
                vertices[index].position.z = mesh->mVertices[index].z;
            }
            
            if (mesh->HasNormals()) {
                vertices[index].normal.x = mesh->mNormals[index].x;
                vertices[index].normal.y = mesh->mNormals[index].y;
                vertices[index].normal.z = mesh->mNormals[index].z;
            }
            
            if (mesh->HasTextureCoords(0)) {
                vertices[index].texcoord.x = mesh->mTextureCoords[0][index].x;
                vertices[index].texcoord.y = mesh->mTextureCoords[0][index].y;
            }
            
            if (mesh->HasTangentsAndBitangents()) {
                vertices[index].tangent.x = mesh->mTangents[index].x;
                vertices[index].tangent.y = mesh->mTangents[index].y;
                vertices[index].tangent.z = mesh->mTangents[index].z;
                vertices[index].bitangent.x = mesh->mBitangents[index].x;
                vertices[index].bitangent.y = mesh->mBitangents[index].y;
                vertices[index].bitangent.z = mesh->mBitangents[index].z;
            }            
        }
		
        /* set indices */
        
        int index;
        
		for (unsigned int f=0; f < mesh->mNumFaces; f++) {			
            
            const struct aiFace* face = &mesh->mFaces[f];
			
			switch (face->mNumIndices) {
				case 1:
					face_mode = GL_POINTS;
					break;
				case 2:
					face_mode = GL_LINES;
					break;
				case 3:
					face_mode = GL_TRIANGLES;
					break;
				default:
					face_mode = GL_POLYGON;
					break;
			}
            
            if (face_mode != GL_TRIANGLES) {
                std::cout << "warning! face is not a triangle." << endl;
            }
			
			for (unsigned int i=0; i < face->mNumIndices; i++) {				
				indices[v_counter] = face->mIndices[i];
			    v_counter++;
            }
		}
        
        qbz::Model* model = new qbz::Model(filename, face_mode);
		model->mesh->set_vertex_buffer(vertices, sizeof(qbz::vertex) * mesh->mNumVertices);
		model->mesh->set_element_buffer(indices, v_counter* sizeof(GLshort));
        model->material = World::loadMaterial(scene->mMaterials[mesh->mMaterialIndex]);

		aiReleaseImport(scene);
		return model;
        
	} else {
        std::cout << "Error! No scene found." << aiGetErrorString() << endl;
    }
	
	return NULL;
}
