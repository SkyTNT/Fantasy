#pragma once

#include <glm/glm.hpp>
#include "Asset.h"

class Mesh : public Asset {
public:
    Mesh();

    ~Mesh() override;

    //���ö������
    void setVerticesCount(unsigned int verticesCount);

    //���ö���λ��
    void setPosition(glm::vec3 *position);

    //���ö���UV
    void setUV(glm::vec2 *uv);

    //���ö��㷨��
    void setNormal(glm::vec3 *normal);

    //���㶥�㷨�ߣ�setNormal��calculateNormal����ѡһ
    void calculateNormal();

    //��������������
    void setIndices(unsigned int count, unsigned int *indices);

    //������ɺ����
    void finish();

    //��ȡ���ƶ���
    unsigned int getObject();

    //�Ƿ�������
    bool hasIndices();

    //��ȡ����������������
    unsigned int getCount();

private:
    unsigned int vao, vbo, ebo, verticesCount, indicesCount;
    glm::vec3 *position, *normal;
    glm::vec2 *uv;
    unsigned int *indices;
};
