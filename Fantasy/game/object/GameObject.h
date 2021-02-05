#pragma once

#include <vector>
#include <typeinfo>

class Component;

class Transform;

//物体
class GameObject {
public:
    GameObject();

    virtual ~GameObject();

    //获取组件，info: typeid(Component class)
    Component *getComponent(const std::type_info &info);

public:
    GameObject *parent;
    std::vector<GameObject *> children;
    std::vector<Component *> components;
    Transform *transform;
};
