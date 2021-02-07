#pragma once

#include <vector>
#include <typeinfo>

class Component;

class Transform;

//����
class GameObject {
public:
    GameObject();

    virtual ~GameObject();

    //��ȡ�����info: typeid(Component class)
    Component *getComponent(const std::type_info &info);
    void addComponent(Component *component);

    void addChild(GameObject *child);

public:
    GameObject *parent;
    std::vector<GameObject *> children;
    std::vector<Component *> components;
    Transform *transform;
};
