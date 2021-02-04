#pragma once
#include <glm/glm.hpp>
#include "Component.h"

class Transform:public Component
{
public:
	explicit Transform(GameObject *gameObject);
	~Transform() override;
	void init() override;
	void tick() override;
    glm::mat4 getMatrix();

public:
	glm::vec3 position, rotation, scale;
private:
    glm::mat4 matrix;
};

