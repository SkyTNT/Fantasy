#include "GameClient.h"
#include <ctime>
#include <utils/Utils.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

static GameClient *mClient;

GameClient::GameClient() : exiting(false), width(0), height(0), lastTime(0) {
    mClient = this;
    input = new Input();
}


GameClient::~GameClient() {
    delete input;
}


void GameClient::exit() {
    exiting = true;
    onExit();
}

unsigned int shader, vao, vbo, ebo,texture0;

float vertices[] = {
        0.5f, 0.5f, 0.0f, 1, 0, 0, 1, 0,  // top right
        0.5f, -0.5f, 0.0f, 0, 1, 0, 1, 1,  // bottom right
        -0.5f, -0.5f, 0.0f, 0, 0, 1, 0, 1,  // bottom left
        -0.5f, 0.5f, 0.0f, 1, 0, 1, 0, 0   // top left
};
unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
};

void GameClient::init(Environment *env) {
    this->env = env;

    //设置输入回调
    input->setKeyCallBack([this](int code, int mods, int action) {
        onKeyEvent(code, mods, action);
    });
    input->setMouseKeyCallBack([this](int code, int mods, int action) {
        onMouseKeyEvent(code, mods, action);
    });
    input->setMouseMoveCallBack([this](float x, float y) {
        onMouseMove(x, y);
    });
    shader = env->createShader(load_asset("tr.vert"), load_asset("tr.frag"));
    vao = env->createObject();
    vbo = env->createVertexBuffer(sizeof(vertices), vertices);
    ebo = env->createElementBuffer(sizeof(indices), indices);
    env->objBindBuffer(vao, vbo, ebo);
    env->objSetVertexLayout(vao, 0, 3, Env::AttribType::Float, 8 * sizeof(float), 0, false);
    env->objSetVertexLayout(vao, 1, 3, Env::AttribType::Float, 8 * sizeof(float), (void *) (3 * sizeof(float)), false);
    env->objSetVertexLayout(vao, 2, 2, Env::AttribType::Float, 8 * sizeof(float), (void *) (6 * sizeof(float)), false);
    int tWidth, tHeight, nrChannels;
    unsigned char *data = stbi_load("../assets/wall.jpg", &tWidth, &tHeight, &nrChannels, 0);
    if (data)
        texture0=env->createTexture2D(Env::ColorType::RGB,tWidth,tHeight,data);
    else
        LOG_E("File","texture load failed");
    stbi_image_free(data);
    env->useShader(shader);
    env->setTexture(shader,"texture0",0);
    env->bindTexture2D(0,texture0);
}

void GameClient::onExit() {
    env->delShader(shader);
    env->delVertexBuffer(vbo);
    env->delElementBuffer(ebo);
    env->delObject(vao);
    env->cleanup();
}

void GameClient::onResize(int width, int height) {

}

void GameClient::onKeyEvent(int code, int mods, int action) {
    switch (code) {
        case INPUT_KEY_ESCAPE:
            exit();
            break;
        default:
            break;
    }
}

void GameClient::onMouseKeyEvent(int code, int mods, int action) {

}

void GameClient::onMouseMove(float x, float y) {

}

void GameClient::tick() {
    //计算间隔时间
    long now = clock();
    long dTimeMs = now - lastTime;
    if (dTimeMs < 0) {
        dTimeMs += LONG_MAX;//防止时间重置
    }
    double dTimeSec = ((float) dTimeMs) / CLOCKS_PER_SEC;

    //检测窗口大小变化
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


void GameClient::render() {
    env->renderStart();
    env->clearColor(glm::vec4(1, 1, 1, 1));
    env->useShader(shader);
    env->drawObject(vao, 6, Env::DrawType::Triangle);
    env->renderEnd();
}

Input *GameClient::getInput() {
    return input;
}

bool GameClient::needExiting() {
    return exiting;
}

GameClient *GameClient::getGameClient() {
    return mClient;
}

