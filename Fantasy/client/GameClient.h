#pragma once
#include "env/Environment.h"

class GameClient
{
public:
	GameClient();
	~GameClient();

	
	void exit();//�˳��ͻ���

	//����
	void init(Environment *env);//��������

	void tick();//֡�¼�
	void render();//��Ⱦ

	//״̬
	bool needExiting();//�Ƿ���Ҫ�˳�

	static GameClient* getGameClient();

private:
	//�¼�����
	void onExit();
	void onResize(int width, int height);//�����ڴ�С�ı�
	void onKeyEvent(int code, int mods, int action);//������̰����¼�
	void onMouseKeyEvent(int code, int mods, int action);//������갴���¼�
	void onMouseMove(float x, float y);//�������λ�ñ仯

private:
	Environment* env;
	int width, height;
	bool exiting;
	long lastTime;

};

