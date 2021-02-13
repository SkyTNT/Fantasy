#pragma once

#include "Component.h"
#include <glm/glm.hpp>

//���
class Camera : public Component {
public:
    Camera();

    void init() override;

    void tick() override;

public:
    //����ɫ
    glm::vec4 clearColor = {0, 0, 0,1};
    //��Ұ���ü��ռ�
    float viewField = 45, near = 0.1f, far = 1000;
    //��ʾid
    unsigned int display = 0;

};
