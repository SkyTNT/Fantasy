#pragma once

class GameObject;

class Component
{
public:

	explicit Component(GameObject *gameObject);
	virtual ~Component();

	virtual void init() = 0;
	virtual void tick() = 0;

    bool initialized;
protected:
    GameObject *gameObject;


};

