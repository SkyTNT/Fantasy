#pragma once

#include <glm/glm.hpp>
#include "Asset.h"

class Mesh : public Asset {
public:
    Mesh();

    ~Mesh() override;

    //设置顶点个数
    void setVerticesCount(unsigned int verticesCount);

    //设置顶点位置
    void setPosition(glm::vec3 *position);

    //设置顶点UV
    void setUV(glm::vec2 *uv);

    //设置顶点法线
    void setNormal(glm::vec3 *normal);

    //计算顶点法线，setNormal与calculateNormal，二选一
    void calculateNormal();

    //设置三角形索引
    void setIndices(unsigned int count, unsigned int *indices);

    //配置完成后调用
    void finish();

    //获取绘制对象
    unsigned int getObject();

    //是否有索引
    bool hasIndices();

    //获取顶点数或者索引数
    unsigned int getCount();

private:
    unsigned int vao, vbo, ebo, verticesCount, indicesCount;
    glm::vec3 *position, *normal;
    glm::vec2 *uv;
    unsigned int *indices;
};
