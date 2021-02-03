#include "GameClient.h"
#include <ctime>
#include <utils/Utils.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <game/asset/Shader.h>
#include <game/asset/Material.h>
#include <game/asset/Mesh.h>

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

Shader *shader;
Texture2D *texture1,*texture2;
Material *material;
Mesh *mesh;

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
    mesh=new Mesh();
    glm::vec3 pos[]={
            {0.5f, 0.5f, 0.0f},
            {0.5f, -0.5f, 0.0f},
            {-0.5f, -0.5f, 0.0f},
            {-0.5f, 0.5f, 0.0f}
    };
    glm::vec3 normal[]={
            {1, 0, 0},
            {0, 1, 0},
            { 0, 0, 1},
            {1, 0, 1}
    };
    glm::vec2 uv[]={
            {1, 0},
            {1,1},
            { 0,1},
            {0,0}
    };
    unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
    };
    mesh->setVerticesCount(4);
    mesh->setPosition(pos);
    mesh->setNormal(normal);
    mesh->setUV(uv);
    mesh->setIndices(6,indices);
    mesh->finish();
    texture1=new Texture2D("../assets/wall.jpg");
    texture2=new Texture2D("../assets/face.png");
    material->set("texture0",texture1);
    material->set("texture1",texture2);
}

void GameClient::onExit() {
    delete shader;
    delete material;
    delete mesh;
    delete texture1;
    delete texture2;
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
    Env::drawObject(mesh->getObject(), mesh->getCount(), Env::DrawType::Triangle, mesh->hasIndices());
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

