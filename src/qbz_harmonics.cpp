#include "qbz_harmonics.h"

using namespace qbz;

#define HARMONICS_SIZE 100

void Harmonics::update(int p1, int p2,int p3,int p4, float f1, float f2, float f3, float f4) {

    param[0] = p1;
    param[1] = p2;
    param[2] = p3;
    param[3] = p4;

    power[0] = f1;
    power[1] = f2;
    power[2] = f3;
    power[3] = f4;

    double du = (M_PI * 2.0) / (double)HARMONICS_SIZE; /* Theta */
    double dv = M_PI / (double)HARMONICS_SIZE;    /* Phi   */

    glm::vec3 tmp;
    int i =0;

    for (int x=0;x<HARMONICS_SIZE; ++x) {
         double u = x * du;
         for (int y=0;y<HARMONICS_SIZE;++y) {
            double v = y * dv;
            tmp = this->eval(u, v);
            vertices[i].position.x = tmp.x;
            vertices[i].position.y = tmp.y;
            vertices[i].position.z = tmp.z;

            vertices[i].texcoord.x = 0.0f;
            vertices[i].texcoord.y = 0.0f;


            tmp = eval(u + du, v);
            vertices[i+1].position.x = tmp.x;
            vertices[i+1].position.y = tmp.y;
            vertices[i+1].position.z = tmp.z;

            vertices[i+1].texcoord.x = 1.0f;
            vertices[i+1].texcoord.y = 0.0f;

            tmp = eval(u + du, v + dv);
            vertices[i+2].position.x = tmp.x;
            vertices[i+2].position.y = tmp.y;
            vertices[i+2].position.z = tmp.z;

            vertices[i+2].texcoord.x = 1.0f;
            vertices[i+2].texcoord.y = 1.0f;

            tmp = eval(u, v + dv);
            vertices[i+3].position.x = tmp.x;
            vertices[i+3].position.y = tmp.y;
            vertices[i+3].position.z = tmp.z;

            vertices[i+3].texcoord.x = 0.0f;
            vertices[i+3].texcoord.y = 1.0f;

            /* calc normals */
            glm::vec3 pos1(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z);
            glm::vec3 pos2(vertices[i+1].position.x, vertices[i+1].position.y, vertices[i+1].position.z);
            glm::vec3 pos3(vertices[i+2].position.x, vertices[i+2].position.y, vertices[i+2].position.z);
            glm::vec3 pos4(vertices[i+3].position.x, vertices[i+3].position.y, vertices[i+3].position.z);

            glm::vec3 normal = calcNormal(pos1, pos2, pos4);
            vertices[i].normal.x = normal.x;
            vertices[i].normal.y = normal.y;
            vertices[i].normal.z = normal.z;

            normal = calcNormal(pos2, pos3, pos1);
            vertices[i+1].normal.x = normal.x;
            vertices[i+1].normal.y = normal.y;
            vertices[i+1].normal.z = normal.z;


            normal = calcNormal(pos3, pos4, pos2);
            vertices[i+2].normal.x = normal.x;
            vertices[i+2].normal.y = normal.y;
            vertices[i+2].normal.z = normal.z;

            normal = calcNormal(pos4, pos1, pos3);
            vertices[i+3].normal.x = normal.x;
            vertices[i+3].normal.y = normal.y;
            vertices[i+3].normal.z = normal.z;

            calcBitangent(vertices[i], vertices[i+1], vertices[i+2]);
            calcBitangent(vertices[i+1], vertices[i+2], vertices[i+3]);
            calcBitangent(vertices[i+2], vertices[i+3], vertices[i]);
            calcBitangent(vertices[i+3], vertices[i+2], vertices[i+1]);

            i += 4;
         }
      }
      this->mesh->update_vertex_buffer(vertices, buffer_size);
}

Harmonics::Harmonics() : Model(GL_QUADS) {

    mesh->vertex_count = HARMONICS_SIZE * HARMONICS_SIZE * 4;
    buffer_size = sizeof(vertex) * this->mesh->vertex_count;

    vertices = (vertex*)malloc(buffer_size);
    if (!vertices) {
        std::cout << "cant allocate vertex buffer\n";
    }

    memset(vertices, buffer_size, 0);

    element_count = (GLuint)this->mesh->vertex_count;
    indices = (GLushort*) malloc(sizeof(GLushort) * element_count);

    double du = (M_PI * 2.0f) / (double)HARMONICS_SIZE; /* Theta */
    double dv = M_PI / (double)HARMONICS_SIZE;    /* Phi   */

    param[0] = 2;
    param[1] = 2;
    param[2] = 2;
    param[3] = 2;

    power[0] = 2.0f;
    power[1] = 2.0f;
    power[2] = 2.0f;
    power[3] = 2.0f;

    glm::vec3 tmp;


    int i=0;

    for (int x=0;x<HARMONICS_SIZE;x++) {
         double u = x * du;
         for (int y=0;y<HARMONICS_SIZE;y++) {
            double v = y * dv;
            tmp = this->eval(u, v);
            vertices[i].position.x = tmp.x;
            vertices[i].position.y = tmp.y;
            vertices[i].position.z = tmp.z;

            vertices[i].texcoord.x = 0.0f;
            vertices[i].texcoord.y = 0.0f;

            tmp = eval(u + du, v);
            vertices[i+1].position.x = tmp.x;
            vertices[i+1].position.y = tmp.y;
            vertices[i+1].position.z = tmp.z;

            vertices[i+1].texcoord.x = 1.0f;
            vertices[i+1].texcoord.y = 0.0f;

            tmp = eval(u + du, v + dv);
            vertices[i+2].position.x = tmp.x;
            vertices[i+2].position.y = tmp.y;
            vertices[i+2].position.z = tmp.z;

            vertices[i+2].texcoord.x = 1.0f;
            vertices[i+2].texcoord.y = 1.0f;

            tmp = eval(u, v + dv);
            vertices[i+3].position.x = tmp.x;
            vertices[i+3].position.y = tmp.y;
            vertices[i+3].position.z = tmp.z;

            vertices[i+3].texcoord.x = 0.0f;
            vertices[i+3].texcoord.y = 1.0f;

            indices[i] = i;
            indices[i+1] = i+1;
            indices[i+2] = i+2;
            indices[i+3] = i+3;

            /* calc normals */
            glm::vec3 pos1(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z);
            glm::vec3 pos2(vertices[i+1].position.x, vertices[i+1].position.y, vertices[i+1].position.z);
            glm::vec3 pos3(vertices[i+2].position.x, vertices[i+2].position.y, vertices[i+2].position.z);
            glm::vec3 pos4(vertices[i+3].position.x, vertices[i+3].position.y, vertices[i+3].position.z);

            glm::vec3 normal = calcNormal(pos1, pos2, pos4);
            vertices[i].normal.x = normal.x;
            vertices[i].normal.y = normal.y;
            vertices[i].normal.z = normal.z;

            normal = calcNormal(pos2, pos3, pos1);
            vertices[i+1].normal.x = normal.x;
            vertices[i+1].normal.y = normal.y;
            vertices[i+1].normal.z = normal.z;


            normal = calcNormal(pos3, pos4, pos2);
            vertices[i+2].normal.x = normal.x;
            vertices[i+2].normal.y = normal.y;
            vertices[i+2].normal.z = normal.z;

            normal = calcNormal(pos4, pos1, pos3);
            vertices[i+3].normal.x = normal.x;
            vertices[i+3].normal.y = normal.y;
            vertices[i+3].normal.z = normal.z;

            calcBitangent(vertices[i], vertices[i+1], vertices[i+2]);
            calcBitangent(vertices[i+1], vertices[i+2], vertices[i+3]);
            calcBitangent(vertices[i+2], vertices[i+3], vertices[i]);
            calcBitangent(vertices[i+3], vertices[i+2], vertices[i+1]);

            i += 4;
         }
      }

    this->mesh->set_vertex_buffer(vertices, buffer_size);
    this->mesh->set_element_buffer(indices, sizeof(GLushort) * element_count);
}

glm::vec3 Harmonics::eval(double theta, double phi) {

    double r = 0;
    glm::vec3 p;

    r += pow(sin(power[0] * phi), (double)param[0]);
    r += pow(cos(power[1] * phi), (double)param[1]);
    r += pow(sin(power[2] * theta), (double)param[2]);
    r += pow(cos(power[3] * theta), (double)param[3]);

    p.x = (float) r * sin(phi) * cos(theta);
    p.y = (float) r * cos(phi);
    p.z = (float) r * sin(phi) * sin(theta);

    return p;
}

glm::vec3 Harmonics::calcNormal(glm::vec3 p1, glm::vec3 p2,glm::vec3 p3) {

    return glm::normalize(glm::cross(p3 - p1, p2 - p1));


}

glm::vec3 Harmonics::calcBitangent(vertex & v1, vertex & v2, vertex & v3) {
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
