#pragma once
#include "env/Environment.h"

class GameClient
{
public:
	GameClient();
	~GameClient();

	
	void exit();//退出客户端

	//设置
	void init(Environment *env);//环境设置

	void tick();//帧事件
	void render();//渲染

	//状态
	bool needExiting();//是否需要退出

	static GameClient* getGameClient();

private:
	//事件处理
	void onExit();
	void onResize(int width, int height);//处理窗口大小改变
	void onKeyEvent(int code, int mods, int action);//处理键盘按键事件
	void onMouseKeyEvent(int code, int mods, int action);//处理鼠标按键事件
	void onMouseMove(float x, float y);//处理鼠标位置变化

private:
	Environment* env;
	int width, height;
	bool exiting;
	long lastTime;

};

