#pragma once
#include "game/object/GameObject.h"
#include "game/asset/Asset.h"
class Scene: public Asset {
public:
    Scene();
    ~Scene() override;

    void init();

public:
    GameObject *root;
};

