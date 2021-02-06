#pragma once

#include "Component.h"
#include <glm/glm.hpp>

//相机
class Camera : public Component {
public:
    explicit Camera(GameObject *gameObject);

    void init() override;

    void tick() override;

public:
    //清屏色
    glm::vec4 clearColor;
    //视野，裁剪空间
    float viewField, near, far;
    //显示id
    unsigned int display;

private:
    //投影矩阵,观察矩阵
    glm::mat4 projection, view;
};
