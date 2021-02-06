#pragma once

#include "Component.h"

class MoveController : public Component {
public:
    explicit MoveController(GameObject *gameObject);
    ~MoveController() override;

    void init() override;
    void tick() override;

private:

};
