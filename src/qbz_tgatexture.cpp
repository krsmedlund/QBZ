#include "qbz_tgatexture.h"

#include <QtDebug>

using namespace qbz;

static short le_short(unsigned char *bytes)
{
    return bytes[0] | ((char)bytes[1] << 8);
}

GLuint TextureLoader::textureFromFile(QString filename)
{
    QImage t;
    QImage b;
    GLuint texture;

    if (!b.load(filename)) {
        QString error("error loading ");  
        error.append(filename);
        qDebug() << error;
        return false;
    }
    
    bool useAlpha = false;
    const uchar* pixelData = b.bits();
    int bytes = b.byteCount();
    
    for (const QRgb* pixel = reinterpret_cast<const QRgb*>(pixelData); bytes > 0; pixel++, bytes -= sizeof(QRgb)) {
        if (qAlpha(*pixel) != UCHAR_MAX) {
            useAlpha = true;
            break;
        }
    }
    
    qDebug() << QString("Loading ") << filename << QString(" with alphachannel ") << useAlpha;
    
    t = QGLWidget::convertToGLFormat(b);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t.width(), t.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits());
    
    return texture;
}
