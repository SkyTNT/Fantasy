#include "GameClient.h"
#include <utils/Utils.h>
#include <game/system/Time.h>
#include <game/system/Window.h>
#include <game/asset/AssetsManager.h>
#include <game/asset/Shader.h>
#include <game/asset/Material.h>
#include <game/asset/Mesh.h>
#include <glm/gtc/matrix_transform.hpp>

static GameClient *mClient;

GameClient::GameClient() : exiting(false){
    mClient = this;
    currentScene = nullptr;
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
Material *material;
Mesh *mesh;

void GameClient::init() {
    Window::update();//让初始化时就能获取窗口大小
    AssetsManager::initAssets();


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

    shader = (Shader *)AssetsManager::getAsset("shader/tr");
    mesh = (Mesh*)AssetsManager::getAsset("mesh/cube");
    material = (Material*)AssetsManager::getAsset("material/cube");

    material->set("projection", glm::perspective(glm::radians(45.0f), Window::width * 1.0f / Window::height, 0.1f, 100.0f));
    material->set("view", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)));
    material->set("model", glm::rotate(glm::mat4(1.0f), glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
}

void GameClient::onExit() {
    AssetsManager::freeAssets();
    Env::cleanup();
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
    Time::update();
    Window::update();
}


void GameClient::render() {
    Env::renderStart();
    Env::clearColor(glm::vec4(1, 1, 1, 1));
    material->use();
    Env::drawObject(mesh->getObject(), mesh->getCount(), Env::DrawType::Triangle, mesh->hasIndices());
    Env::renderEnd();
}

void GameClient::loadScene(Scene *scene) {
    this->currentScene = scene;
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

