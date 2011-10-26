#ifndef QBZ_LIBRARY_H
#define QBZ_LIBRARY_H

#include "qbz.h"

namespace qbz {

    class Resource
    {
    public:
        virtual GLuint handle() {};
    };


    class Texture : public Resource
    {
    public:
        Texture(const std::string & filename);
        GLuint handle();

        bool hasNormalMap, hasSpecularMap, hasAlphaChannel;

    private:
        GLuint textureHandle;

        // actually has a alpha value != 1.0 somewhere in the image
        bool usesAlphaChannel;

        int bytes;
        const uchar* pixelData;
        QImage baseImage, textureImage;
    };


    class Library
    {
    public:
        static Library & open() { static Library instance; return instance; }

        Texture* getTexture(const std::string & name);
        QGLShaderProgram* getShader(const std::string & name);

        ResourceType getResourceType(const std::string & name);
        std::map<std::string, ResourceType> * getResourceList();
        std::vector<std::string> getResourceListByType(ResourceType type);

    private:
        void recursiveFind(ResourceType type, QDir & path, int recLevel=0);
        void addResource(ResourceType type, const std::string & name);

        std::map<std::string, Texture*> loadedTextureList;
        std::map<std::string, QGLShaderProgram*> loadedShaderList;
        std::map<std::string, ResourceType> availResourceList;

        Library();
        Library(Library const &);              // Don't Implement
        void operator=(Library const&); // Don't implement
    };

};

#endif // QBZ_LIBRARY_H
