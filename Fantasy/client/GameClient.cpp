#include "GameClient.h"
#include <ctime>
#include <utils/Utils.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <game/asset/Shader.h>
#include <game/asset/Material.h>

static GameClient *mClient;

GameClient::GameClient() : exiting(false), width(0), height(0), lastTime(0) {
    mClient = this;
    input = new Input();
}


GameClient::~GameClient() {
    onExit();
    delete input;
}


void GameClient::exit() {
    exiting = true;
}

unsigned int  vao, vbo, ebo;
Shader *shader;
Texture2D *texture2D;
Material *material;

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

void GameClient::init() {

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
    shader = new Shader("tr.vert","tr.frag");
    material=new Material(shader);
    vao = Env::createObject();
    vbo = Env::createVertexBuffer(sizeof(vertices), vertices);
    ebo = Env::createElementBuffer(sizeof(indices), indices);
    Env::objBindBuffer(vao, vbo, ebo);
    Env::objSetVertexLayout(vao, 0, 3, Env::AttribType::Float, 8 * sizeof(float), 0, false);
    Env::objSetVertexLayout(vao, 1, 3, Env::AttribType::Float, 8 * sizeof(float), (void *) (3 * sizeof(float)), false);
    Env::objSetVertexLayout(vao, 2, 2, Env::AttribType::Float, 8 * sizeof(float), (void *) (6 * sizeof(float)), false);
    texture2D=new Texture2D("../assets/wall.jpg");
    material->set("texture0",*texture2D);
}

void GameClient::onExit() {
    delete shader;
    Env::delVertexBuffer(vbo);
    Env::delElementBuffer(ebo);
    Env::delObject(vao);
    Env::cleanup();
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
    int newWidth = Env::getWindowWidth();
    int newHeight = Env::getWindowHeight();
    bool sizeChanged = width != newWidth || height != newHeight;
    width = newWidth;
    height = newHeight;
    if (sizeChanged) {
        onResize(newWidth, newHeight);
    }
    lastTime = clock();
}


void GameClient::render() {
    Env::renderStart();
    Env::clearColor(glm::vec4(1, 1, 1, 1));
    material->use();
    Env::drawObject(vao, 6, Env::DrawType::Triangle);
    Env::renderEnd();
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

