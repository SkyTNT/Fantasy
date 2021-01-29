#pragma once
#include <vector>
#include "../component/Transform.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

public:
	std::vector<GameObject*> children;
	std::vector<Component*> components;
	Transform* transform;
};

