#include "GameClient.h"
#include <ctime>
#include <utils/Utils.h>
#include <game/asset/Shader.h>
#include <game/asset/Material.h>
#include <game/asset/Mesh.h>
#include <glm/gtc/matrix_transform.hpp>

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

    //��������ص�
    input->setKeyCallBack([this](int code, int mods, int action) {
        onKeyEvent(code, mods, action);
    });
    input->setMouseKeyCallBack([this](int code, int mods, int action) {
        onMouseKeyEvent(code, mods, action);
    });
    input->setMouseMoveCallBack([this](float x, float y) {
        onMouseMove(x, y);
    });
    width = Env::getWindowWidth();
    height = Env::getWindowHeight();

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
    texture1=new Texture2D("wall.jpg");
    texture2=new Texture2D("face.png");
    material->set("texture0",texture1);
    material->set("texture1",texture2);
    material->set("texture0",texture1);
    material->set("projection",glm::perspective(glm::radians(45.0f), width*1.0f / height, 0.1f, 100.0f));
    material->set("view",glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)));
    material->set("model", glm::rotate(glm::mat4(1.0f), glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
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
    //������ʱ��
    long now = clock();
    long dTimeMs = now - lastTime;
    if (dTimeMs < 0) {
        dTimeMs += LONG_MAX;//��ֹʱ������
    }
    double dTimeSec = ((float) dTimeMs) / CLOCKS_PER_SEC;

    //��ⴰ�ڴ�С�仯
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

