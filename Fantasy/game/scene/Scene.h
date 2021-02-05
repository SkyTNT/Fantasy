#pragma once
#include "game/object/GameObject.h"
#include "game/asset/Asset.h"
//场景
class Scene: public Asset {
public:
    Scene();
    ~Scene() override;
    //被加载时调用
    virtual void init();
    //每帧调用
    virtual void tick();
public:
    //根节点
    GameObject *root;
};

