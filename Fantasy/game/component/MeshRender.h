#pragma once
#include "Component.h"
class Material;
class MeshRender: public Component {
public:
    explicit MeshRender(GameObject* gameObject);

    void init() override;
    void tick() override;

    Material*material;
};

