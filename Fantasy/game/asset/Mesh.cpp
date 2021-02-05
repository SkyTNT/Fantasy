#include "Mesh.h"
#include <env/Environment.h>

Mesh::Mesh() {
    vao = Env::createObject();
    vbo = 0;
    ebo = 0;
    indicesCount = 0;
    verticesCount = 0;
    position = nullptr;
    uv = nullptr;
    normal = nullptr;
    indices = nullptr;
}

Mesh::~Mesh() {
    Env::delObject(vao);
    if (vbo)
        Env::delVertexBuffer(vbo);
    if (ebo)
        Env::delElementBuffer(ebo);

}

void Mesh::setIndices(unsigned int count, unsigned int *indices) {
    indicesCount = count;
    this->indices = indices;
}

void Mesh::setVerticesCount(unsigned int verticesCount) {
    this->verticesCount = verticesCount;
}

void Mesh::setPosition(glm::vec3 *position) {
    this->position = position;
}

void Mesh::setUV(glm::vec2 *uv) {
    this->uv = uv;
}

void Mesh::setNormal(glm::vec3 *normal) {
    this->normal = normal;
}

void Mesh::calculateNormal() {

}

void Mesh::finish() {
    //临时顶点数组
    float *vertices = new float[verticesCount * 8];
    //把顶点属性按照position,normal,uv放置
    for (int i = 0; i < verticesCount; ++i) {
        unsigned int offset = i * 8;
        memcpy(&vertices[offset], &position[i], sizeof(glm::vec3));
        memcpy(&vertices[offset + 3], &normal[i], sizeof(glm::vec3));
        memcpy(&vertices[offset + 6], &uv[i], sizeof(glm::vec2));
    }

    //把顶点数组放入Buffer
    vbo = Env::createVertexBuffer(verticesCount * sizeof(float) * 8, vertices, Env::MemoryType::Static);
    if (indices)
        ebo = Env::createElementBuffer(indicesCount * sizeof(unsigned int), indices, Env::MemoryType::Static);

    //绑定Buffer，设置顶点布局
    Env::objBindBuffer(vao, vbo, ebo);
    Env::objSetVertexLayout(vao, 0, 3, Env::AttribType::Float, 8 * sizeof(float), 0, false);
    Env::objSetVertexLayout(vao, 1, 3, Env::AttribType::Float, 8 * sizeof(float), (void *) (3 * sizeof(float)), false);
    Env::objSetVertexLayout(vao, 2, 2, Env::AttribType::Float, 8 * sizeof(float), (void *) (6 * sizeof(float)), false);
    delete[] vertices;
}

unsigned int Mesh::getObject() {
    return vao;
}

unsigned int Mesh::getCount() {
    return indicesCount == 0 ? verticesCount : indicesCount;
}

bool Mesh::hasIndices() {
    return indicesCount != 0;
}
