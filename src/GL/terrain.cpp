#include "terrain.h"

using namespace qbz;

#define TERRAIN_SIZE 100

Terrain::Terrain(float bl_x, float bl_y, float tr_x, float tr_y) : Model("Terrain", GL_QUADS) {

    this->mesh.vertex_count = TERRAIN_SIZE * TERRAIN_SIZE;
    buffer_size = sizeof(vertex) * this->mesh.vertex_count;
    quad_count = (TERRAIN_SIZE-1) * (TERRAIN_SIZE-1);

    vertices = (vertex*)malloc(buffer_size);
    if (!vertices) {
        std::cout << "cant allocate vertex buffer\n";
    }
    memset(vertices, buffer_size, 0);

    /* grid layout */



    step = 200.0f / (float)TERRAIN_SIZE;



    int i=0;
    for (int row=0; row < TERRAIN_SIZE; row++) {
        for (int col=0; col < TERRAIN_SIZE; col++) {

            float x = (float)col * step;
            float y = (float)row * step;

            vertices[i].position.x = -100.0f + x;
            vertices[i].position.y = 0.1f;
            vertices[i].position.z = -100.0f + y;

            vertices[i].texcoord.x = bl_x + (tr_x - bl_x) * x;
            vertices[i].texcoord.y = tr_y - (tr_y - bl_y) * y;

            vertices[i].normal.x = 0.0f;
            vertices[i].normal.y = 1.0f;
            vertices[i].normal.z = 0.0f;
            i++;
        }
    }

    switch (this->mesh.primitive_type) {
        case GL_POINTS:
            element_count = (GLuint)this->mesh.vertex_count;
            indices = (GLushort*) malloc(sizeof(GLushort) * element_count);
            for (GLuint ei=0; ei < element_count; ei++) {
                this->indices[ei] = ei;
            }
            break;

        case GL_LINE_LOOP:
        case GL_QUADS:
            element_count = (quad_count)*4;
            indices = (GLushort*) malloc(sizeof(GLushort) * element_count);
            if (!vertices) {
                std::cout << "cant allocate index buffer\n";
            }
            memset(indices, 0, sizeof(GLushort) * element_count);
            GLushort v=0;
            for (GLushort ind=0; ind < element_count - 4; ind+=4) {
                indices[ind] = v + TERRAIN_SIZE;
                indices[ind+1] = v + TERRAIN_SIZE + 1;
                indices[ind+2] = v + 1;
                indices[ind+3] = v;
                v++;
                if (!((v + 1) % TERRAIN_SIZE)) v++;
            }
            break;
    }

    this->mesh.set_vertex_buffer(vertices, buffer_size);
    this->mesh.set_element_buffer(indices, sizeof(GLushort) * element_count);
}

glm::vec3 calcNormal(glm::vec3 p1, glm::vec3 p2,glm::vec3 p3) {

    return glm::normalize(glm::cross(p3 - p1, p2 - p1));


}

glm::vec3 calcBitangent(vertex & v1, vertex & v2, vertex & v3) {
    glm::vec3 p1 = glm::vec3(v1.position.x, v1.position.y, v1.position.z);
    glm::vec3 p2 = glm::vec3(v2.position.x, v2.position.y, v2.position.z);
    glm::vec3 p3 = glm::vec3(v3.position.x, v3.position.y, v3.position.z);

    glm::vec3 edge1 = p2 -p1;
    glm::vec3 edge2 = p3 - p1;
    glm::vec2 edge1uv = glm::vec2(v2.texcoord.x, v2.texcoord.y) - glm::vec2(v1.texcoord.x, v1.texcoord.y);
    glm::vec2 edge2uv = glm::vec2(v3.texcoord.x, v3.texcoord.y) - glm::vec2(v1.texcoord.x, v1.texcoord.y);

    float cp = edge1uv.y * edge2uv.x - edge1uv.x * edge2uv.y;

    if (cp != 0.0f) {
        float mul = 1.0f / cp;
        glm::vec3 tangent   = (edge1 * -edge2uv.y + edge2 * edge1uv.y) * mul;
        glm::vec3 bitangent = (edge1 * -edge2uv.x + edge2 * edge1uv.x) * mul;

        tangent = glm::normalize(tangent);
        bitangent = glm::normalize(bitangent);

        v1.tangent.x = tangent.x;
        v1.tangent.y = tangent.y;
        v1.tangent.z = tangent.z;

        v1.bitangent.x = bitangent.x;
        v1.bitangent.y = bitangent.y;
        v1.bitangent.z = bitangent.z;
    }

}


vertex * Terrain::getSurroundingVertices(int i) {

    qbz::vertex* v[5];
    v[5] = NULL;

    glm::vec3 normal;

    // first corner
    if (i == 0) {
        v[0] = &(vertices[i+1]);  // right of
        v[1] = &(vertices[i+TERRAIN_SIZE]); // above

        normal = calcNormal(
                    glm::vec3(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z), //p1
                    glm::vec3(v[0]->position.x, v[0]->position.y, v[0]->position.z), //p1
                    glm::vec3(v[1]->position.x, v[1]->position.y, v[1]->position.z) //p1
                    );
        normal = glm::normalize(-normal);
        vertices[i].normal.x = normal.x;
        vertices[i].normal.y = normal.y;
        vertices[i].normal.z = normal.z;
        calcBitangent(vertices[i], *v[0], *v[1]);

    }

    // second corner
    else if (i == TERRAIN_SIZE-1) {
        v[0] = &(vertices[i-1]);  // left of
        v[1] = &(vertices[i+TERRAIN_SIZE]); // above
        normal = calcNormal(
                    glm::vec3(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z), //p1
                    glm::vec3(v[0]->position.x, v[0]->position.y, v[0]->position.z), //p1
                    glm::vec3(v[1]->position.x, v[1]->position.y, v[1]->position.z) //p1
                    );
        normal = glm::normalize(-normal);
        vertices[i].normal.x = normal.x;
        vertices[i].normal.y = normal.y;
        vertices[i].normal.z = normal.z;
        calcBitangent(vertices[i], *v[0], *v[1]);
    }

    // third corner
    else if (i == (TERRAIN_SIZE * TERRAIN_SIZE) - TERRAIN_SIZE) {
        v[0] = &(vertices[i+1]);  // right of
        v[1] = &(vertices[i-TERRAIN_SIZE]); // below
        normal = calcNormal(
                    glm::vec3(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z), //p1
                    glm::vec3(v[0]->position.x, v[0]->position.y, v[0]->position.z), //p1
                    glm::vec3(v[1]->position.x, v[1]->position.y, v[1]->position.z) //p1
                    );
        normal = glm::normalize(-normal);
        vertices[i].normal.x = normal.x;
        vertices[i].normal.y = normal.y;
        vertices[i].normal.z = normal.z;
        calcBitangent(vertices[i], *v[0], *v[1]);

    }

    // fourth corner
    else if (i == (TERRAIN_SIZE * TERRAIN_SIZE)-1) {
        v[0] = &(vertices[i-1]);  // left of
        v[1] = &(vertices[i-TERRAIN_SIZE]); // below
        normal = calcNormal(
                    glm::vec3(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z), //p1
                    glm::vec3(v[0]->position.x, v[0]->position.y, v[0]->position.z), //p1
                    glm::vec3(v[1]->position.x, v[1]->position.y, v[1]->position.z) //p1
                    );
        normal = glm::normalize(-normal);
        vertices[i].normal.x = normal.x;
        vertices[i].normal.y = normal.y;
        vertices[i].normal.z = normal.z;
        calcBitangent(vertices[i], *v[0], *v[1]);

    }

    // bottom edge
    else if (i < TERRAIN_SIZE-1) {
        v[0] = &(vertices[i+1]);  // right of
        v[1] = &(vertices[i+TERRAIN_SIZE]); // above
        v[2] = &(vertices[i-1]); // left of
        normal = calcNormal(
                    glm::vec3(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z), //p1
                    glm::vec3(v[0]->position.x, v[0]->position.y, v[0]->position.z), //p1
                    glm::vec3(v[1]->position.x, v[1]->position.y, v[1]->position.z) //p1
                    );
        normal += calcNormal(
                    glm::vec3(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z), //p1
                    glm::vec3(v[1]->position.x, v[1]->position.y, v[1]->position.z), //p1
                    glm::vec3(v[2]->position.x, v[2]->position.y, v[2]->position.z) //p1
                    );
        normal = glm::normalize(-normal);
        vertices[i].normal.x = normal.x;
        vertices[i].normal.y = normal.y;
        vertices[i].normal.z = normal.z;
        calcBitangent(vertices[i], *v[0], *v[1]);

    }

    // bottom edge
    else if (i > (TERRAIN_SIZE * TERRAIN_SIZE) - TERRAIN_SIZE) {
        v[0] = &(vertices[i+1]);  // right of
        v[1] = &(vertices[i-TERRAIN_SIZE]); // below
        v[2] = &(vertices[i-1]); // left of
        normal = calcNormal(
                    glm::vec3(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z), //p1
                    glm::vec3(v[0]->position.x, v[0]->position.y, v[0]->position.z), //p1
                    glm::vec3(v[1]->position.x, v[1]->position.y, v[1]->position.z) //p1
                    );
        normal += calcNormal(
                    glm::vec3(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z), //p1
                    glm::vec3(v[1]->position.x, v[1]->position.y, v[1]->position.z), //p1
                    glm::vec3(v[2]->position.x, v[2]->position.y, v[2]->position.z) //p1
                    );
        normal = glm::normalize(-normal);
        vertices[i].normal.x = normal.x;
        vertices[i].normal.y = normal.y;
        vertices[i].normal.z = normal.z;
        calcBitangent(vertices[i], *v[0], *v[1]);

    }


    // left side
    else if( 0 == i%TERRAIN_SIZE) {
        v[0] = &(vertices[i-TERRAIN_SIZE]);  // below
        v[1] = &(vertices[i+1]); // right of
        v[2] = &(vertices[i+TERRAIN_SIZE]); // labove
        normal = calcNormal(
                    glm::vec3(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z), //p1
                    glm::vec3(v[0]->position.x, v[0]->position.y, v[0]->position.z), //p1
                    glm::vec3(v[1]->position.x, v[1]->position.y, v[1]->position.z) //p1
                    );
        normal += calcNormal(
                    glm::vec3(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z), //p1
                    glm::vec3(v[1]->position.x, v[1]->position.y, v[1]->position.z), //p1
                    glm::vec3(v[2]->position.x, v[2]->position.y, v[2]->position.z) //p1
                    );
        normal = glm::normalize(-normal);
        vertices[i].normal.x = normal.x;
        vertices[i].normal.y = normal.y;
        vertices[i].normal.z = normal.z;

        calcBitangent(vertices[i], *v[0], *v[1]);

    }

    // right side
    else if( TERRAIN_SIZE-1 == i%TERRAIN_SIZE) {
        v[0] = &(vertices[i-TERRAIN_SIZE]);  // below
        v[1] = &(vertices[i-1]); // left of
        v[2] = &(vertices[i-TERRAIN_SIZE]); // above
        normal = calcNormal(
                    glm::vec3(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z), //p1
                    glm::vec3(v[0]->position.x, v[0]->position.y, v[0]->position.z), //p1
                    glm::vec3(v[1]->position.x, v[1]->position.y, v[1]->position.z) //p1
                    );
        normal += calcNormal(
                    glm::vec3(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z), //p1
                    glm::vec3(v[1]->position.x, v[1]->position.y, v[1]->position.z), //p1
                    glm::vec3(v[2]->position.x, v[2]->position.y, v[2]->position.z) //p1
                    );
        normal = glm::normalize(-normal);
        vertices[i].normal.x = normal.x;
        vertices[i].normal.y = normal.y;
        vertices[i].normal.z = normal.z;
        calcBitangent(vertices[i], *v[0], *v[1]);

    }

    else {
        v[0] = &(vertices[i-TERRAIN_SIZE]);  // below
        v[1] = &(vertices[i-1]); // left of
        v[2] = &(vertices[i+TERRAIN_SIZE]); // above
        v[3] = &(vertices[i+1]); // right of

        normal = calcNormal(
                    glm::vec3(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z), //p1
                    glm::vec3(v[0]->position.x, v[0]->position.y, v[0]->position.z), //p1
                    glm::vec3(v[1]->position.x, v[1]->position.y, v[1]->position.z) //p1
                    );
        normal += calcNormal(
                    glm::vec3(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z), //p1
                    glm::vec3(v[1]->position.x, v[1]->position.y, v[1]->position.z), //p1
                    glm::vec3(v[2]->position.x, v[2]->position.y, v[2]->position.z) //p1
                    );
        normal += calcNormal(
                    glm::vec3(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z), //p1
                    glm::vec3(v[2]->position.x, v[2]->position.y, v[2]->position.z), //p1
                    glm::vec3(v[3]->position.x, v[3]->position.y, v[3]->position.z) //p1
                    );
        normal += calcNormal(
                    glm::vec3(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z), //p1
                    glm::vec3(v[3]->position.x, v[3]->position.y, v[3]->position.z), //p1
                    glm::vec3(v[0]->position.x, v[0]->position.y, v[0]->position.z) //p1
                    );

        normal = glm::normalize(-normal);
        vertices[i].normal.x = normal.x;
        vertices[i].normal.y = normal.y;
        vertices[i].normal.z = normal.z;
        calcBitangent(vertices[i], *v[0], *v[1]);

    }
}

void Terrain::populateFromHeightMap(const std::string &filename) {
    QImage t;
    QImage b;
    GLuint texture;

    if (!b.load(QString(filename.c_str()))) {
        QString error("error loading ");
        error.append(filename.c_str());
        qDebug() << error;
    }

    const uchar* pixelData = b.bits();
    int bytes = b.byteCount();
    const QRgb* pixel = reinterpret_cast<const QRgb*>(pixelData);

    for (int i=0; bytes > 0 && i<this->mesh.vertex_count; ++i) {
        bytes -= sizeof(QRgb);
        vertices[i].position.y = 0.5f + qRed(*pixel) / 255.0f;
        pixel++;
    }

    for (int i=0; i<this->mesh.vertex_count; ++i) {
        this->getSurroundingVertices(i);
    }

    this->mesh.update_vertex_buffer(vertices, this->mesh.vertex_count*sizeof(vertex));

}


void Terrain::populateFromNoise(int seed) {

    srand(seed);

    for (int i=0; i<this->mesh.vertex_count; ++i) {
        vertices[i].position.y += cos(vertices[i].position.x) + sin(vertices[i].position.z/2.0); // rand() / (float)RAND_MAX / 2.0f;

    }

    for (int i=0; i<this->mesh.vertex_count; ++i) {
        this->getSurroundingVertices(i);
    }

    this->mesh.update_vertex_buffer(vertices, this->mesh.vertex_count*sizeof(vertex));
}
