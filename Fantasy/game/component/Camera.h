#pragma once
#include "Component.h"

class Camera: public Component {
public:
    explicit Camera(GameObject * gameObject);

    void init() override;
    void tick() override;
};

