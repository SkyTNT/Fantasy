#pragma once

#include "Component.h"

class Material;

//������Ⱦ��
class MeshRender : public Component {
public:
    MeshRender();

    void init() override;

    void tick() override;

public:
    Material *material;
};