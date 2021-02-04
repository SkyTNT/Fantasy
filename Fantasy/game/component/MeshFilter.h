#pragma once
#include "Component.h"
#include <string>
class Mesh;

class MeshFilter: public Component {
public:
    explicit MeshFilter(GameObject* gameObject);
    void init() override;
    void tick() override;

public:
    Mesh* mesh;
};

