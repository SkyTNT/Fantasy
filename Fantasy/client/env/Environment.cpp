#include "Environment.h"

Environment::Environment()
{
	input = new Input();
	nExit = false;
}

Environment::~Environment()
{
	delete input;
}

Input * Environment::getInput()
{
	return input;
}

bool Environment::needExit()
{
	return nExit;
}


bool Environment::setup(void *args)
{
	return true;
}

void Environment::exit()
{
	nExit = true;
}
