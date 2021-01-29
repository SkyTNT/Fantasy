#pragma once
class Component
{
public:
	Component();
	virtual ~Component();

	virtual void tick(double dTime) = 0;
};

