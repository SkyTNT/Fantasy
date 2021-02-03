#pragma once
#include <glm/glm.hpp>
class Mesh {
public:
    Mesh();
    ~Mesh();
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
    void setIndices(unsigned int count,unsigned int *indices);
    //配置完成后调用
    void finish();

    unsigned int getObject();
    bool hasIndices();
    unsigned int getCount();

private:
    unsigned int vao,vbo,ebo,verticesCount,indicesCount;
    glm::vec3 *position,*normal;
    glm::vec2 *uv;
    unsigned int *indices;
};
