#pragma once
#include "Component.h"
class Material;

//������Ⱦ��
class MeshRender: public Component {
public:
    explicit MeshRender(GameObject* gameObject);

    void init() override;
    void tick() override;

public:
    Material*material;
};

