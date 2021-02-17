#pragma once

class GameObject;

//组件
class Component {
public:

    Component();

    virtual ~Component();

    //第一帧调用
    virtual void init() = 0;

    //每帧调用
    virtual void tick() = 0;

public:
    bool initialized = false;
protected:
    GameObject *gameObject = nullptr;

    friend GameObject;
};
