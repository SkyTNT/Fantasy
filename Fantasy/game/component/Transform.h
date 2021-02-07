#pragma once

#include <glm/glm.hpp>
#include "Component.h"

//�任������������ԣ�
class Transform : public Component {
public:
    Transform();

    ~Transform() override;

    void init() override;

    void tick() override;

    //��ȡ�任����
    glm::mat4 getMatrix();

public:
    glm::vec3 position, rotation, scale;
private:
    glm::mat4 matrix;
};
