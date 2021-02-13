#pragma once

#include "Component.h"
#include <string>

class Mesh;

//Íø¸ñ×é¼þ
class MeshFilter : public Component {
public:
    MeshFilter();

    void init() override;

    void tick() override;

public:
    Mesh *mesh = nullptr;
};
