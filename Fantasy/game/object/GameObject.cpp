#include "GameObject.h"



GameObject::GameObject()
{
	transform = new Transform();
	components.push_back(transform);
}


GameObject::~GameObject()
{
	delete transform;
	children.clear();
	children.shrink_to_fit();
	components.clear();
	components.shrink_to_fit();
}
