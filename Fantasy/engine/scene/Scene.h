#pragma once

#include <object/GameObject.h>
#include <asset/Asset.h>

//����
class Scene : public Asset {
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
