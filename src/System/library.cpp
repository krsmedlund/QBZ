#include "library.h"
#include "tgatexture.h"

using namespace qbz;

GLuint Texture::handle() { return textureHandle; }

Texture::Texture(const std::string & name)
{
    QString filename("data/textures/");
    filename.append(name.c_str());

    if (!baseImage.load(filename)) {
        QString error("error loading ");
        error.append(filename);
        qDebug() << error;
    }

    usesAlphaChannel = false;
    const uchar* pixelData = baseImage.bits();
    bytes = baseImage.byteCount();

    for (const QRgb* pixel = reinterpret_cast<const QRgb*>(pixelData); bytes > 0; pixel++, bytes -= sizeof(QRgb)) {
        if (qAlpha(*pixel) != UCHAR_MAX) {
            usesAlphaChannel = true;
            break;
        }
    }
    textureImage = QGLWidget::convertToGLFormat(baseImage);
    glGenTextures(1, &textureHandle);
    glBindTexture(GL_TEXTURE_2D, textureHandle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage.width(), textureImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage.bits());

}


Library::Library()
{
    /* load resource list */

    QDir imageDir("./");
    recursiveFind(QBZ_RESOURCE_TEXTURE, imageDir);
}

void Library::addResource(ResourceType type, const std::string & name) {
    //qDebug() << "available resource added:" << name.c_str();
    availResourceList[name] = type;
}

void Library::recursiveFind(ResourceType type, QDir & path, int recLevel)
{
    QDir d("data/textures/");
    d.setSorting( QDir::Name );
    d.setFilter( QDir::Files | QDir::Dirs );

    QStringList qsl = d.entryList();

    foreach (QString entry, qsl) {
        QFileInfo finfo(entry);
        if (finfo.isSymLink()) continue;
        if (finfo.isDir()) {
            QString dirname = finfo.fileName();
            if ((dirname==".") || (dirname == "..")) continue;
            QDir sd(finfo.filePath());
            this->recursiveFind(type, sd, recLevel++);
         } else {
            addResource(type, finfo.fileName().toStdString());
        }
    }
}

Texture* Library::getTexture(const std::string & name)
{
    Texture * res;

    if (loadedTextureList.count(name) > 0) {
        res = loadedTextureList[name];
    }

    else if (availResourceList.count(name) > 0) {
        res = new Texture(name);
        loadedTextureList[name] = res;
    }

    return res;
}

QGLShaderProgram* Library::getShader(const std::string & name)
{
    if (loadedShaderList.count(name)) {
        return loadedShaderList[name];
    }

    const QGLContext* context = QGLContext::currentContext();

    std::string n("data/" + name + ".vert");
    QString vertFile(n.c_str());
    std::string n2("data/" + name + ".frag");
    QString fragFile(n2.c_str());

    QGLShaderProgram* program = new QGLShaderProgram(context);

    if (!program->addShaderFromSourceFile(QGLShader::Vertex, vertFile)) {
        qDebug() << "Error from vertex compile: " << program->log();
    } else if (!program->addShaderFromSourceFile(QGLShader::Fragment, fragFile)) {
        qDebug() << "Error from fragment compile: " << program->log();
    }else if (!program->link()) {
        qDebug() << "Error from linking: " << program->log();
    } else  {
        this->loadedShaderList[name] = program;
    }
    return program;
}
