#pragma once
#include "game/object/GameObject.h"
#include "game/asset/Asset.h"
//����
class Scene: public Asset {
public:
    Scene();
    ~Scene() override;
    //������ʱ����
    virtual void init();
    //ÿ֡����
    virtual void tick();
public:
    //���ڵ�
    GameObject *root;
};

