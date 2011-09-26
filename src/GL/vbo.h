#ifndef QBZ_VBO_H
#define QBZ_VBO_H

#include "qbz.h"

namespace qbz {
class VBO
{
public:

    VBO(int);
    void setElementBuffer(const GLushort* data, GLsizei len);
    void setVertexBuffer(struct vertex* data, GLsizei len);
    void updateElementBuffer(const GLushort* data, GLsizei len, GLsizei offset);
    void updateVertexBuffer(struct vertex* data, GLsizei len , GLsizei offset);

    vertex * allocateVertices(int nVertices);
    vertex * getVertex(int nVertex);

    void bind();
    void release();

private:
    int maxVertices;
    int freeVertices;

    const GLushort* elementBufferData;
    vertex* vertexBufferData;

    GLuint vertexBuffer;
    GLuint elementBuffer;

    GLint vertexBufferDataLength;
    GLint elementBufferDataLength;

};


};

#endif // QBZ_VBO_H
