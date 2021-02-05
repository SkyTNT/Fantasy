#pragma once
#include "Component.h"
#include <glm/glm.hpp>

class Camera: public Component {
public:
    explicit Camera(GameObject * gameObject);

    void init() override;
    void tick() override;

public:
    glm::vec3 clearColor;
    float viewField,near,far;
    unsigned int display;

private:
    glm::mat4 projection,view;
};

