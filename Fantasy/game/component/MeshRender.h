#pragma once

#include "Component.h"

class Material;

//Íø¸ñäÖÈ¾Æ÷
class MeshRender : public Component {
public:
    MeshRender();

    void init() override;

    void tick() override;

public:
    Material *material;
};