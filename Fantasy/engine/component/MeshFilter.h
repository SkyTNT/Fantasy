#pragma once

#include "Component.h"
#include <string>

class Mesh;

//�������
class MeshFilter : public Component {
public:
    MeshFilter();

    void init() override;

    void tick() override;

public:
    Mesh *mesh = nullptr;
};
