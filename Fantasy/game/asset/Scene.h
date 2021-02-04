#pragma once
#include "../object/GameObject.h"
#include "Asset.h"
class Scene: public Asset {
public:
    Scene();
    ~Scene() override;

    void init();

public:
    std::vector<GameObject*> gameObjects;

};

