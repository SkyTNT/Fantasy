#pragma once
#include <env/Environment.h>
#include "input/Input.h"
#include <game/scene/Scene.h>

class GameClient
{
public:
	GameClient();
	~GameClient();

    //初始化
    void init();
    //退出客户端
	void exit();

    //帧事件
	void tick();
	//加载场景
	void loadScene(Scene *scene);

	Input* getInput();
	bool needExiting();//是否需要退出

	static GameClient* getGameClient();

private:
	//事件处理
	void onExit();
	void onKeyEvent(int code, int mods, int action);//处理键盘按键事件
	void onMouseKeyEvent(int code, int mods, int action);//处理鼠标按键事件
	void onMouseMove(float x, float y);//处理鼠标位置变化
private:
    Input *input;
	bool exiting;
	Scene *currentScene;
};

