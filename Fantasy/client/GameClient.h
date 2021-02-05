#pragma once
#include <env/Environment.h>
#include "input/Input.h"
#include <game/scene/Scene.h>

class GameClient
{
public:
	GameClient();
	~GameClient();

    //��ʼ��
    void init();
    //�˳��ͻ���
	void exit();

    //֡�¼�
	void tick();
	//���س���
	void loadScene(Scene *scene);

	Input* getInput();
	bool needExiting();//�Ƿ���Ҫ�˳�

	static GameClient* getGameClient();

private:
	//�¼�����
	void onExit();
	void onKeyEvent(int code, int mods, int action);//������̰����¼�
	void onMouseKeyEvent(int code, int mods, int action);//������갴���¼�
	void onMouseMove(float x, float y);//�������λ�ñ仯
private:
    Input *input;
	bool exiting;
	Scene *currentScene;
};

