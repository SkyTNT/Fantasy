#pragma once

class GameObject;

//���
class Component {
public:

    Component();

    virtual ~Component();

    //��һ֡����
    virtual void init() = 0;

    //ÿ֡����
    virtual void tick() = 0;

public:
    bool initialized = false;
protected:
    GameObject *gameObject = nullptr;

    friend GameObject;
};
