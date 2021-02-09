#pragma once

#include "Component.h"
#include <glm/glm.hpp>

class Transform;

class MoveController : public Component {
public:
    MoveController();
    ~MoveController() override;

    void init() override;
    void tick() override;

private:
    Transform *transform;
    glm::vec3 move;
    float pitch,yaw;

};
