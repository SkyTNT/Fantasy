#pragma once
#include <glm/glm.hpp>
#include "Component.h"

class Transform:public Component
{
public:
	Transform();
	~Transform() override;
	void tick(double dTime) override;

public:
	glm::vec3 position, rotation, scale;
};

