#pragma once

#include <glm/glm.hpp>
#include "Component.h"

//变换（物体基本属性）
class Transform : public Component {
public:
    Transform();

    ~Transform() override;

    void init() override;

    void tick() override;

    //获取变换矩阵
    glm::mat4 getMatrix();

public:
    glm::vec3 position, rotation, scale;
private:
    glm::mat4 matrix;
};
