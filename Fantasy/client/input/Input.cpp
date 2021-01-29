#include "Input.h"
#include "Input.h"



Input::Input()
{

}


Input::~Input()
{

}

void Input::sendKeyEvent(int code, int mods, int action)
{
	keyCallBack(code,mods,action);
}

void Input::sendMouseKeyEvent(int code, int mods, int action)
{
	mouseKeyCallBack(code, mods, action);
}

void Input::sendMouseMove(float x, float y)
{
	mouseMoveCallBack(x, y);
}

void Input::setKeyCallBack(std::function<void(int, int, int)> keyCallBack)
{
	this->keyCallBack = keyCallBack;
}

void Input::setMouseKeyCallBack(std::function<void(int, int, int)> mouseKeyCallBack)
{
	this->mouseKeyCallBack = mouseKeyCallBack;
}

void Input::setMouseMoveCallBack(std::function<void(float, float)> mouseMoveCallBack)
{
	this->mouseMoveCallBack = mouseMoveCallBack;
}

