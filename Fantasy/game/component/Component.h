#pragma once

class GameObject;

//���
class Component {
public:

    explicit Component(GameObject *gameObject);

    virtual ~Component();

    //��һ֡����
    virtual void init() = 0;

    //ÿ֡����
    virtual void tick() = 0;

public:
    bool initialized;
protected:
    GameObject *gameObject;


};
