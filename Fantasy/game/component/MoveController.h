#pragma once

#include "Component.h"
#include <glm/glm.hpp>

class MoveController : public Component {
public:
    MoveController();
    ~MoveController() override;

    void init() override;
    void tick() override;

private:
    glm::vec4 center,right,front,up,move;
    float pitch,yaw;

};
