#pragma once

#include "Component.h"
#include <glm/glm.hpp>

//相机
class Camera : public Component {
public:
    Camera();

    void init() override;

    void tick() override;

public:
    //清屏色
    glm::vec4 clearColor = {0, 0, 0,1};
    //视野，裁剪空间
    float viewField = 45, near = 0.1f, far = 1000;
    //显示id
    unsigned int display = 0;

};
