#include "vbo.h"

using namespace qbz;

VBO::VBO(int nBytes)
{
    maxVertices = nBytes / sizeof(struct vertex);
    freeVertices = maxVertices;

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, nBytes, 0, GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ARRAY_BUFFER, nBytes, 0, GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void VBO::updateElementBuffer(const GLushort* data, GLsizei len, GLsizei offset){}
void VBO::updateVertexBuffer(struct vertex* data, GLsizei len , GLsizei offset){}

vertex * VBO::allocateVertices(int nVertices){}
vertex * VBO::getVertex(int nVertex){}

void VBO::bind(){}
void VBO::release(){}
