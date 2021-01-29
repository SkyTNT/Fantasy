#include "GameClient.h"
#include <ctime>
#include <utils/Utils.h>

static GameClient* mClient;

GameClient::GameClient():exiting(false),width(0),height(0),lastTime(0)
{
	mClient = this;
}


GameClient::~GameClient()
{

}


void GameClient::exit()
{
	exiting = true;
	onExit();
}

const char *vertexShaderSource = "#version 300 es\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 300 es\n"
                                   "out mediump  vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";

unsigned int shader,vao,vbo,ebo;

float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
};

void GameClient::init(Environment * env)
{
	this->env = env;

	//��������ص�
	Input* input = env->getInput();
	input->setKeyCallBack([this](int code, int mods, int action) {
		onKeyEvent(code, mods, action);
	});
	input->setMouseKeyCallBack([this](int code, int mods, int action) {
		onMouseKeyEvent(code, mods, action);
	});
	input->setMouseMoveCallBack([this](float x, float y) {
		onMouseMove(x, y);
	});
	shader = env->createShader(vertexShaderSource, fragmentShaderSource);

	vao = env->createObject();
	vbo = env->createVertexBuffer(sizeof(vertices), vertices);
	ebo = env->createElementBuffer(sizeof(indices), indices);
	env->objBindBuffer(vao, vbo, ebo);
	env->objSetVertexLayout(vao, 0, 3, Env::AttribType::Float, 3 * sizeof(float), 0, false);
}

void GameClient::onExit()
{
	env->delShader(shader);
	env->delVertexBuffer(vbo);
	env->delElementBuffer(ebo);
	env->delObject(vao);
	env->cleanup();
}

void GameClient::onResize(int width, int height)
{
	
}

void GameClient::onKeyEvent(int code, int mods, int action)
{
	switch (code)
	{
	case INPUT_KEY_ESCAPE:
		exit();
		break;
	default:
		break;
	}
}

void GameClient::onMouseKeyEvent(int code, int mods, int action)
{

}

void GameClient::onMouseMove(float x, float y)
{

}

void GameClient::tick()
{
	//������ʱ��
	long now = clock();
	long dTimeMs = now - lastTime;
	if (dTimeMs < 0) {
		dTimeMs += LONG_MAX;//��ֹʱ������
	}
	double dTimeSec = ((float)dTimeMs) / CLOCKS_PER_SEC;
	
	//��ⴰ�ڴ�С�仯
	int newWidth = env->getWindowWidth();
	int newHeight = env->getWindowHeight();
	bool sizeChanged = width != newWidth || height != newHeight;
	width = newWidth;
	height = newHeight;
	if (sizeChanged) {
		onResize(newWidth, newHeight);
	}
	lastTime = clock();
}


void GameClient::render()
{
	env->renderStart();
	env->useShader(shader);
	env->drawObject(vao, 6, Env::DrawType::Triangle);
	env->renderEnd();
}

bool GameClient::needExiting()
{
	return exiting||env->needExit();
}

GameClient* GameClient::getGameClient()
{
	return mClient;
}