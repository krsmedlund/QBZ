#include "modelfile.h"

using namespace qbz;
using namespace qbz::model;

const std::string & ModelFile::getType()
{
    return "ModelFile";
}

static qbz::network::NetworkNode* ModelFileFactoryCreator(const std::string & nodeName)
{
    ModelFile* f = new ModelFile(nodeName);
    f->loadMesh(nodeName);
    return f;
}

static int foo = qbz::network::Factory::registerCreateFunction("ModelFile", ModelFileFactoryCreator);


ModelFile::ModelFile(const std::string & nodeName)
    : Model(nodeName)
{
}

void ModelFile::loadMaterial(const struct aiMaterial *mtl)
{
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
        material.diffuse = glm::vec4(diffuse.r, diffuse.g, diffuse.b, diffuse.a);

    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
        material.specular = glm::vec4(specular.r, specular.g, specular.b, specular.a);

    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
        material.diffuse = glm::vec4(ambient.r, ambient.g, ambient.b, ambient.a);

    //if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
    //    mat->diffuse = glm::vec4(emission.r, emission.g, emission.b, emission.a);

    max = 1;
    ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);

    max = 1;
    ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);

    if((ret1 == AI_SUCCESS) && (ret2 == AI_SUCCESS)) {
        material.strength = strength;
        material.shininess = shininess;
    } else {
        material.shininess = 0.0f;
        material.strength = 0.0f;
        material.specular = glm::vec4(0.0f);
    }

    max = 1;
    if(AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
        material.fill_mode = wireframe ? GL_LINE : GL_FILL;
    else
        material.fill_mode = GL_FILL;

    max = 1;
    if((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
        material.two_sided = false;
    else
        material.two_sided = true;
}


void ModelFile::loadMesh(const std::string & filename)
{
    GLuint scene_list = 0;
    const aiScene* scene = NULL;
    aiVector3D scene_min, scene_max, scene_center;
    static float angle = 0.f;
    GLenum face_mode;

    const aiMesh* mesh;

    std::string path = "./data/models/" + filename;

    //Assimp::Importer importer;
    scene = aiImportFile(path.c_str(),
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

        this->mesh.set_vertex_buffer(vertices, sizeof(qbz::vertex) * mesh->mNumVertices);
        this->mesh.set_element_buffer(indices, v_counter* sizeof(GLshort));
        loadMaterial(scene->mMaterials[mesh->mMaterialIndex]);
        aiReleaseImport(scene);

     } else {
        std::cout << "Error! No scene found." << aiGetErrorString() << std::endl;
     }
}
