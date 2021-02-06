#pragma once

#include "Component.h"
#include <glm/glm.hpp>

//���
class Camera : public Component {
public:
    explicit Camera(GameObject *gameObject);

    void init() override;

    void tick() override;

public:
    //����ɫ
    glm::vec4 clearColor;
    //��Ұ���ü��ռ�
    float viewField, near, far;
    //��ʾid
    unsigned int display;

private:
    //ͶӰ����,�۲����
    glm::mat4 projection, view;
};
