#pragma once

#include "Component.h"
#include <glm/glm.hpp>

class Transform;

class MoveController : public Component {
public:
    MoveController();

    void init() override;
    void tick() override;

private:
    Transform *transform = nullptr;
    glm::vec3 move = {0,0,0};
    float pitch = 0,yaw = 0;

};
